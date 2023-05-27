#include "shell.h"

/**
 * _cd - to change current directory
 * @arg: information
 *
 * Return: 0
 */

int _cd(arg_t *arg)
{
	if (_strcmp(arg->argv[0], "cd", _strlen("cd")) == 0)
	{
		if (arg->argv[1])
		{
			if (chdir(arg->argv[1]) != 0)
			{
				write(STDERR_FILENO, "Could not change directory to '%s'\n",
						(size_t)arg->argv[1]);
				return (1);
			}
			else
				chdir(getenv("HOME"));
		}
	}
	return (0);
}

