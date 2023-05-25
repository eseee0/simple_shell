#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @arg: Structure containing potential arguments. Used to maintain
 *	    constant function prototype.
 * Return: Always 0
 */

char **get_environ(arg_t *arg)
{
	if (!arg->environ || arg->env_changed)
	{
		arg->environ = list_to_strings(arg->env);
		arg->env_changed = 0;
	}

return (arg->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @arg: information
 *
 * Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(arg_t *arg, char *var)
{
	list_t *node = arg->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);
	while (node)
	{
		p = strstr(node->str, var);
		if (p && *p == '=')
		{
			arg->env_changed = delete_node_at_index(&(arg->env), i);
			i = 0;
			node = arg->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (arg->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *	       or modify an existing one
 * @arg: information
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
 
int _setenv(arg_t *arg, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);
	buf = malloc(strlen(var) + strlen(value) + 2);
	if (!buf)
		return (1);
	strcpy(buf, var);
	strcat(buf, "=");
	strcat(buf, value);
	node = arg->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			arg->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(arg->env), buf, 0);
	free(buf);
	arg->env_changed = 1;
	return (0);
}

