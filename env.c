#include "shell.h"

/**
 * _myenv - prints the current environment
 * @arg: Structure containing potential arguments. Used to maintain
 *	    constant function prototype.
 * Return: Always 0
 */
int _myenv(arg_t *arg)
{
	list_t *node = arg->env;

	while (node)
	{
		write(STDOUT_FILENO, node->str, strlen(node->str));
		write(STDOUT_FILENO, "\n", 1);
		node = node->next;
	}
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @arg: struct information
 * @name: env var name
 *
 * Return: value
 */
char *_getenv(arg_t *arg, const char *name)
{
	list_t *node = arg->env;
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - to initialize a new env variable
 * @arg: struct information
 *
 *  Return: 0
 */
int _mysetenv(arg_t *arg)
{
	char *value;
	int ret;

	if (arg->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	value = getenv(arg->argv[1]);
	if (value)
		unsetenv(arg->argv[1]);
	ret = setenv(arg->argv[1], arg->argv[2], 1);
	if (ret != 0)
	{
		_eputs("Error setting environment variable.\n");
		return (1);
	}
	return (0);
}

/**
 * _myunsetenv - to remove an environment variable
 * @arg: struct information
 * Return: 0
 */

int _myunsetenv(arg_t *arg)
{

	int i;
	int ret;

	if (arg->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}

	for (i = 1; i <= arg->argc; i++)
	{
		ret = unsetenv(arg->argv[i]);
		if (ret != 0)
		{
			_eputs("Error unsetting environment variable.\n");
			return (1);
		}
	}
	return (0);
}

/**
 * populate_env_list - to populate env linked list
 * @arg: struct information
 *
 * Return: 0
 */

int populate_env_list(arg_t *arg)
{
	list_t *node = NULL;
	size_t i;

	arg->env = NULL;
	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	arg->env = node;
	return (0);
}
