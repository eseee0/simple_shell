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
