#include "shell.h"

/**
 * check_file_status - checks the status of a file.
 * @pathname: path of the file to check.
 *
 * Return: True if file exits, else False
 */

bool check_file_status(char *pathname)
{
	int stat_return;
	struct stat stat_buf;

	stat_return = stat(pathname, &stat_buf);

	if (stat_return == 0)
	{
		if (S_ISREG(stat_buf.st_mode) == 0)
			return (false);

		if (access(pathname, X_OK) == 0)
			return (true);

		return (false);
	}

	return (false);
}

/**
 * handle_path - searches for the command in the directories specified by PATH
 * @cmd: command to search for
 *
 * Return: null
 */

void handle_path(char *cmd)
{
	char *path = getenv("PATH");
	char *dir;
	size_t path_len;
	size_t cmd_len;
	size_t full_path_len;
	char *full_path;

	for (dir = strtok(path, ":"); dir != NULL;)
	{
		path_len = _strlen(dir);
		cmd_len = _strlen(cmd);
		full_path_len = path_len + cmd_len + 2;
		full_path = malloc(full_path_len);

		write(STDOUT_FILENO, dir, path_len);
		write(STDOUT_FILENO, "/", 1);
		write(STDOUT_FILENO, cmd, cmd_len);

		if (access(full_path, F_OK) != -1)
		{
			int _execute(char *cmd, char **argv);
			free(full_path);
			return;
		}
		free(full_path);
	}
	write(STDOUT_FILENO, "Command not found\n", 18);
}

/**
 * _execute - executes a command with the given arguments
 * @cmd: command to execute
 * @argv: array of arguments for the command
 *
 * Return: 0 (Success), else -1
 */

int _execute(char *cmd, char **argv)
{
	pid_t pid = fork();

	if (pid == 0)
	{
		execve(cmd, argv,  environ);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	wait(NULL);
	return (0);

}

/**
 * shell_prompt - to display a shell prompt and execute user commands
 * @av: array of command-line arguments
 * @env: array of environment variables
 */

void shell_prompt(char **av, char **env)
{
	char *buff = NULL;
	int i, j;
	size_t buffsize = 0;
	ssize_t num_char;
	pid_t wpid;
	int p;
	char *cmd_path = NULL;


	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		num_char = getline(&buff, &buffsize, stdin);
		if (num_char == -1)
		{
			free(buff);
			exit(EXIT_FAILURE);
		}

		buff[num_char-1] = '\0';

		i = 0;
		while (buff[i])
		{
			if (buff[i] == '\n')
				buff[i] = 0;
			i++;
		}

		j = 0;
		av[j] = strtok(buff, " "); /* or use argv[0] */
		while (av[j] != NULL) /* can remove "!= NULL" */
		{
			j++;
			av[j] = strtok(NULL, " ");
		}

		if (_strcmp(av[0], "exit", _strlen(av[0])) == 0)
		{
			free(buff);
			exit(EXIT_SUCCESS);
		}

		wpid = fork();
		if (wpid == -1)
		{
			free(buff);
			exit(EXIT_FAILURE);
		}
		if (wpid == 0)
		{
			if (access(av[0], F_OK) != -1)
				execve(av[0], av, env);
			else
			{
				write(STDERR_FILENO, av[0], _strlen(av[0]));
				write(STDERR_FILENO, ": No such file or directory\n", 28);
			}
			free(buff);
			exit(EXIT_FAILURE);
		}
		else
		{
			char *path = getenv("PATH");
			int cmd_len;
			int path_len;

			if (path != NULL)
			{
				char *token = strtok(path, ":");

				while (token != NULL)
				{
					path_len = _strlen(token);
					cmd_len = _strlen(av[0]);
					 if (path_len + cmd_len + 1 < BUFFER_SIZE)
					 {
						 cmd_path = malloc(path_len + cmd_len + 2);
						 _strcpy(cmd_path, token);
						 cmd_path[path_len] = '/';
						 _strcat(cmd_path + path_len + 1, av[0]);
						 if (access(cmd_path, F_OK) != -1)
						 {
							 p = 1;
							 break;
						 }
					 }
					 token = strtok(NULL, ":");
				}
			}
		}
		if (p)
		{
			execve(cmd_path, av, env);
			perror("execve");
		}
		else
			wait(NULL);
		free(cmd_path);
	}
}
