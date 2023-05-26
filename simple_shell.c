#include "shell.h"

/**
 * hsh - Executes the specified command by searching for the executable file in the system's PATH directories.
 *
 * @param arg   A structure containing command arguments, such as argc (argument count), argv (argument vector), and envp (environment variables).
 * @param av    An array of command arguments.
 *
 * @Return: exit status
 */

int hsh(arg_t *arg)
{
    int argc = arg->argc;
    char **argv = arg->argv;
    int i;
    int status;
    char *path;
    char *full_path;
    char *dir;
    pid_t pid;

    for (i = 0; i < argc; i++)
    {
        if (argv[i][0] == '-')
            continue;

        path = getenv("PATH");
        if (path == NULL)
	{
            perror("Could not find PATH environment variable");
            return (1);
        }

        full_path = NULL;
        dir = strtok(path, ":");

        while (dir != NULL)
	{
            full_path = malloc(_strlen(dir) + _strlen(argv[i]) + 2);
            if (full_path == NULL)
	    {
                perror("Could not allocate memory for full path");
                return (1);
            }

            _strcpy(full_path, dir);
            _strcat(full_path, "/");
	    _strcat(full_path, argv[i]);

            if (access(full_path, F_OK) == 0)
                break;

            free(full_path);
            full_path = NULL;
            dir = strtok(NULL, ":");
        }

        if (full_path == NULL)
	{
            perror("Could not find executable file for '%s'");
            return (1);
        }

        pid = fork();

        if (pid == -1)
	{
            perror("Fork failed");
            return (1);
        }
	else if (pid == 0)
	{
            status = execve(full_path, argv, arg->envp);
            perror("Could not execute '%s'");
            exit(1);
        }
	else
	{
            wait(&status);
            return (WEXITSTATUS(status));
        }
    }

    return (0);
}

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */

int shell(int ac, char **av)
{
        arg_t arg;
        int fd = 0;

        if (ac == 2)
                fd = open(av[1], O_RDONLY);
        if (fd == -1)
        {
                if (errno == EACCES)
                        exit(126);
                else if (errno == ENOENT)
                {
                        _eputs(av[0]);
                        _eputs(": 0: Can't open ");
                        _eputs(av[1]);
                        _eputs((char *) '\n');
                        _eputchar(BUF_FLUSH);
                        exit(127);
                }
                else
                        return (EXIT_FAILURE);
        }
        arg.readfd = fd;

	if (pop_env_list(&arg) != 0)
		return (EXIT_FAILURE);

        /** if (read_history(&arg) != 0)
                return (EXIT_FAILURE); */
        if (hsh(&arg) != 0)
                return (EXIT_SUCCESS);
	close(fd);
        return (EXIT_SUCCESS);
}


