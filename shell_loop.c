#include "shell.h"

/**
 * hsh - main shell loop
 * @arg: the parameter & return arg struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */

int hsh(arg_t *arg, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_arg(arg);
		if (is_interactive(arg))
		{
			_puts("$ ");
			_eputchar(BUF_FLUSH);
		}
		r = get_input(arg);
		if (r != -1)
		{
			set_arg(arg, av);
			builtin_ret = find_builtin(arg);
			if (builtin_ret == -1)
				find_cmd(arg);
			else if (is_interactive(arg))
				_putchar('\n');
		}
		free_arg(arg, 0);
	}
	write_history(arg);
	free_arg(arg, 1);
	if (!is_interactive(arg) && arg->status)
		exit(arg->status);
	if (builtin_ret == -2)
	{
		if (arg->err_num == -1)
			exit(arg->status);
		exit(arg->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @arg: the parameter & return arg struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit()
 */

int find_builtin(arg_t *arg)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", exit_shell},
		{"env", _myenv},
		{"help", _help},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _cd},
		{"alias", _myalias},
		{NULL, NULL}
	};
	for (i = 0; builtintbl[i].type; i++)
	{
		if (_strcmp(arg->argv[0], builtintbl[i].type) == 0)
		{
			arg->line_count++;
			built_in_ret = builtintbl[i].func(arg);
			break;
		}
	}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @arg: the parameter & return arg struct
 *
 * Return: void
 */

void find_cmd(arg_t *arg)
{
	char *path = NULL;
	int i, k;

	arg->path = arg->argv[0];

	if (arg->linecount_flag == 1)
	{
		arg->line_count++;
		arg->linecount_flag = 0;
	}
	for (i = 0, k = 0; arg->arg[i]; i++)
	{
		if (!is_delimiter(arg->arg[i], " \t\n"))
			k++;
	}
	if (!k)
		return;
	path = find_path(arg, _getenv(arg, "PATH="), arg->argv[0]);
	if (path)
	{
		arg->path = path;
		fork_cmd(arg);
	}
	else
	{
		if ((is_interactive(arg) || _getenv(arg, "PATH=") || arg->argv[0][0] == '/')
				&& is_cmd(arg, arg->argv[0]))
			fork_cmd(arg);
		else if (*(arg->arg) != '\n')
		{
			arg->status = 127;
			print_error(arg, "not found\n");
		}
		else
		{
			arg->status = 127;
			print_error(arg, "command not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @arg: the parameter & return arg struct
 *
 * Return: void
 */
void fork_cmd(arg_t *arg)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(arg->path, arg->argv, get_environ(arg)) == -1)
		{
			free_arg(arg, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(arg->status));
		if (WIFEXITED(arg->status))
		{
			arg->status = WEXITSTATUS(arg->status);
			if (arg->status == 126)
				print_error(arg, "Permission denied\n");
		}
	}
}
