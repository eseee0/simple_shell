#include "shell.h"

/**
 * exit_shell - to exit the shell
 * @arg: information about function
 *
 * Return: exit status
 */

int exit_shell(arg_t *arg)
{
	if (_strcmp(arg->argv[0], "exit", _strlen("exit")) == 0)
	{
		if (arg->argv[1])
		{
			int exit_status = _atoi(arg->argv[1]);

			if (exit_status < 0)
			{
				write(STDERR_FILENO, "Illegal number: %d\n", exit_status);
				return (1);
			}
			write(STDOUT_FILENO, "exit\n", 5);
			exit(exit_status);
		}
		else
		{
			write(STDOUT_FILENO, "exit\n", 5);
			exit(0);
		}
	}
	return (0);
}
