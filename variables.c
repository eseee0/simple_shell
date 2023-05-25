#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @arg: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */

int is_chain(arg_t *arg, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		arg->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		arg->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		arg->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @arg: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */

void check_chain(arg_t *arg, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (arg->cmd_buf_type == CMD_AND)
	{
		if (arg->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (arg->cmd_buf_type == CMD_OR)
	{
		if (!arg->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	*p = j;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @arg: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */

int replace_alias(arg_t *arg)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(arg->alias, arg->argv[0], '=');
		if (!node)
			return (0);
	}
	free(arg->argv[0]);
	p = strchr(node->str, '=');
	if (!p)
		return (0);
	p = strdup(p + 1);
	if (!p)
		return (0);
	arg->argv[0] = p;
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @arg: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */

int replace_vars(arg_t *arg)
{
	int i = 0;
	list_t *node;

	for (i = 0; arg->argv[i]; i++)
	{
		if (arg->argv[i][0] != '$' || !arg->argv[i][1])
			continue;

		if (!_strcmp(arg->argv[i], "$?"))
		{
			replace_string(&(arg->argv[i]),
					_strdup(convert_number(arg->status, 10, 0)));
			continue;
		}
		if (!_strcmp(arg->argv[i], "$$"))
		{
			replace_string(&(arg->argv[i]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(arg->env, &arg->argv[i][1], '=');
		if (node)
		{
			replace_string(&(arg->argv[i]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&arg->argv[i], _strdup(""));

	}
	return (0);
}


/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */

int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

