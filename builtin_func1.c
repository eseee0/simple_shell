#include "shell.h"

/**
 * _hist - to display history list
 * @arg: information
 *
 *  Return: 0
 */

int _hist(arg_t *arg)
{
        print_list(arg->history);
        return (0);
}

/**
 * alias_unset - unset alias from  string
 * @arg: struct
 * @str: string
 *
 * Return: 0 (Success), else 1
 */

int alias_unset(arg_t *arg, char *str)
{
        int ret;
	char *a;
	list_t *node;

        a = _strcat(str, "=");
        if (!a)
                return (1);

        *a = '\0';
	node = arg->alias;
        ret = get_node_index(node, a);
	if (!ret)
		return (1);
        return (0);
}

/**
 * alias_set - to set alias to string
 * @arg: struct
 * @str: string
 *
 * Return: 0 (Success), else 1
 */

int alias_set(arg_t *arg, char *str)
{
        char *a;

        a = _strchr(str, '=');
        if (*(a + 1) == '\0')
                alias_unset(arg, str);
	else
	{
        	alias_unset(arg, str);
        	if (add_node_end(&(arg->alias), str, 0) == NULL)
                	return (1);
	}
        if (!a)
                return (1);
        return (0);
}

/**
 * alias_print - to print alias string
 * @node: node
 *
 * Return: 0 (Success), else 1
 */

int alias_print(list_t *node)
{
        char *a = NULL;
	char *b = NULL;

        if (node)
        {
                a = _strchr(node->str, '=');
                for (b = node->str; b <= a; b++)
                	_putchar(*b);
                _puts(a + 1);
                _puts("'\n");
                return (0);
        }
        return (1);
}

/**
 * _alias - alias builtin custom
 * @arg: information
 *
 * Return: 0
 */

int _alias(arg_t *arg)
{
        char *a = NULL;
	char *c = NULL;
        list_t *node = NULL;
        int i = 0;

        if (arg->argc == 1)
        {
                node = arg->alias;
                while (node)
                {
			_putchar('\'');
			for (c = node->str; *c; c++)
				_putchar(*c);
			_putchar('\'');
			_putchar('=');
			_putchar('\'');
			_putchar('\'');
			_putchar('\n');
                        print_list(node);
                        node = node->next;
                }
                return (0);
        }
        for (i = 1; arg->argv[i]; i++)
        {
                a = _strchr(arg->argv[i], '=');
                if (a)
                        alias_set(arg, arg->argv[i]);
                else
                        alias_print(node_starts_with(arg->alias, arg->argv[i], '='));
        }

        return (0);
}
