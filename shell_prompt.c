#include "shell.h"
#include <sys/wait.h>

/**
 * shell_prompt - Displays a prompt and reads user input to execute commands.
 * @av: The arguments passed to the program.
 * @env: The environment variables.
 *
 * Return: void
 */


void shell_prompt(char **av, char **env)
{
	char *buff = NULL;
	int i, status;
	size_t buffsize = 0;
	ssize_t num_char;
	char *argv[] = {NULL, NULL};
	pid_t wpid;


	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");

		num_char = getline(&buff, &buffsize, stdin);
		if (num_char == -1)
		{
			free(buff);
			exit(EXIT_FAILURE);
		}
		i = 0;
		while (buff[i])
		{
			if (buff[i] == '\n')
				buff[i] = 0;
			i++;
		}
		argv[0] = buff;
		wpid = fork();
		if (wpid == -1)
		{
			free(buff);
			exit(EXIT_FAILURE);
		}
		if (wpid == 0)
		{
			if (execve(argv[0], argv, env) == -1)
				printf("%s: No such file or directory\n", av[0]);

		}
		else
			wait(&status);
	}
}
