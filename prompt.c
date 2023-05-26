#include "shell.h"

int main(int argc, char **argv)
{
	char *buff = NULL;
	int i;
	int status;
	size_t buffsize = 0;
	ssize_t num_char;
	pid_t wpid;


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
		for (i = 0; i < argc; i++)
		{
			if (buff[i] == '\n')
				buff[i] = 0;
		}

		argv[0] = strtok(buff, " "); /* or use argv[0] */
		for (i = 1; argv[i] != NULL; i++)
			argv[i] = strtok(NULL, " "); /* delete j++ and do argv[++j] = strtok(NULL, " "); for reduced lines */	
		wpid = fork();
		if (wpid == -1)
		{
			free(buff);
			exit(EXIT_FAILURE);
		}
		if (wpid == 0)
		{
			if (execve(argv[0], argv, environ))
			{
				write(STDERR_FILENO, argv[0], _strlen(argv[0]));
				write(STDERR_FILENO, ": No such file or directory\n", 28);
			}
		}
		else 
			wait(&status);
	}
	return (0);
}

