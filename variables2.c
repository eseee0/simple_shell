#include "shell.h"

/**
 * execute_command - executes a command
 * @arg: the parameter struct
 *
 * Return: 1 if success, 0 otherwise
 */

int execute_command(arg_t *arg)
{
	int status;

	if (arg->cmd_buf_type == CMD_OR)
	{
		status = system(arg->argv[0]);
		if (status != 0)
			return (0);
	}
	else if (arg->cmd_buf_type == CMD_AND)
	{
		status = system(arg->argv[0]);
		if (status != 0)
			return (0);
	}
	else if (arg->cmd_buf_type == CMD_CHAIN)
	{
		status = system(arg->argv[0]);
		if (status != 0)
			return (0);
	}
	return (1);
}

/**
 * parse_command - parses a command line
 * @buf: the command line buffer
 * @arg: the parameter struct
 *
 * Return: 1 if success, 0 otherwise
 */

int parse_command(char *buf, arg_t *arg)
{
	char *argv[10];
	int argc = 0;
	size_t i;

	for (i = 0; buf[i]; i++)
	{
		if (buf[i] == ' ' || buf[i] == '\t')
			continue;
	argv[argc++] = buf + i;
	while (buf[i] != ' ' && buf[i] != '\t' && buf[i] != '\0')
		i++;
	if (buf[i] == '\0')
		break;
	}
	argv[argc] = NULL;
	arg->argv = argv;
	arg->argc = argc;
	return (1);
}
