#include "shell.h"

/**
 * main - entry point of the shell program
 * @argc: number of command-line arguments
 * @argv: array of command-line arguments
 * @env: array of environment variables
 *
 * Return: Always 0
 */

int main(int argc, char **argv, char **env)
{
	arg_t *exit_arg = malloc(sizeof(arg_t));

	if (exit_arg == NULL)
		return (1);

	exit_arg->argv = malloc(2 * sizeof(char *));
	if (exit_arg->argv == NULL)
	{
		free(exit_arg);
		return (1);
	}
	exit_arg->argv[0] = _strdup("exit");
	exit_arg->argv[1] = NULL;

	if (argc == 1)
		shell_prompt(argv, env);
	else if (argc == 2 && _strcmp(argv[1], "exit", _strlen("exit")) == 0)
		exit_shell(exit_arg);

	free(exit_arg->argv[0]);
	free(exit_arg->argv);
	free(exit_arg);

	return (0);
}
