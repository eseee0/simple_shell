#include "shell.h"

/**
 * main - Entry point
 * @ac: The number of command line arguments.
 * @av: An array of strings containing the command line arguments.
 * @env: An array of strings containing the environment variables.
 *
 * Return: Always 0.
 */
int main(int ac, char **av, char **env)
{
	if (ac == 1)
		shell_prompt(av, env);

	return (0);
}
