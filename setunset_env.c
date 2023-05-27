#include "shell.h"

/**
 * get_env - to get env variable value
 * @arg: struct information
 * @name: name of env variable
 *
 * Return: value
 */

char *get_env(arg_t *arg, const char *name)
{
	list_t *node = arg->env;
	char *a = NULL;

	while (node)
	{
		a = starts_with(node->str, name);
		if (a && *a)
			return (a);
		node = node->next;
	}
	return (NULL);
}


/**
 * unset_env - to remove env variable
 * @arg: struct information
 *
 * Return: 0
 */

int unset_env(arg_t *arg)
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
		ret = unset_env((arg_t *)arg->argv[i]);
		if (ret != 0)
		{
			_eputs("Error unsetting environment variable.\n");
			return (1);
		}
	}
	return (0);
}

/**
 * set_env - get new env
 * @arg: struct information
 *
 *  Return: 0
 */

int set_env(arg_t *arg)
{
	char *value;
	int i = 0;

	value = get_env(arg, arg->argv[i]);
	if (value == NULL)
	{
		value = _strdup(arg->argv[2]);
		if (value == NULL)
		{
			_eputs("Error allocating memory.\n");
			return (1);
		}

		setenv(arg->argv[1], value, 1);
	}
	else
		setenv(arg->argv[1], value, 1);

	return (0);
}
