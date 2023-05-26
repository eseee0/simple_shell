#include "shell.h"

/**
 * _env - to print current environment
 * @arg: information
 *
 * Return: Always 0
 */

int _env(arg_t *arg)
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

/**
 * pop_env_list - to populate env linked list
 * @arg: struct information
 *
 * Return: 0
 */

int pop_env_list(arg_t *arg)
{
        list_t *node = NULL;
        size_t i;

        arg->env = NULL;
        for (i = 0; environ[i]; i++)
                add_node_end(&node, environ[i], 0);
        arg->env = node;
        return (0);
	if (node != NULL)
		free(node);
}
