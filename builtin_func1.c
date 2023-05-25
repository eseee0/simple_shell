#include "shell.h"

/**
 * _myhistory - to display history list
 * @arg: information
 *
 *  Return: 0
 */
int _myhistory(arg_t *arg)
{
	print_list(arg->history);
	return (0);
}

/**
 * unset_alias - to unset alias from  string
 * @arg: struct
 * @str: string alias
 *
 * Return: 0 (Success), else 1
 */
int unset_alias(arg_t *arg, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(arg->alias),
		get_node_index(arg->alias, node_starts_with(arg->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - to set alias to string
 * @arg: struct
 * @str: string alias
 *
 * Return: 0 (Success), else 1
 */

int set_alias(arg_t *arg, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(arg, str));

	unset_alias(arg, str);
	if (add_node_end(&(arg->alias), str, 0) == NULL)
		return (1);
	return (0);
}

/**
 * print_alias - to print  alias string
 * @node: alias node
 *
 * Return: 0 (Success), else 1
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @arg: information
 *  Return: 0
 */
int _myalias(arg_t *arg)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (arg->argc == 1)
	{
		node = arg->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; arg->argv[i]; i++)
	{
		p = _strchr(arg->argv[i], '=');
		if (p)
			set_alias(arg, arg->argv[i]);
		else
			print_alias(node_starts_with(arg->alias, arg->argv[i], '='));
	}

	return (0);
}
