#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @arg: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(arg_t *arg, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
		for (;;)
		{
			r = getline(buf, &len_p, stdin);
			if (r == -1)
			{
				if (errno == EINTR)
					continue;
				else
					return -1;
			}
			if (r == 0)
				break;
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			arg->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(arg, *buf, arg->histcount++);
			{
				*len = r;
				arg->cmd_buf = buf;
				break;
			}
		}
	}
  return (r);
}

/**
 * get_input - gets a line minus the newline
 * @arg: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(arg_t *arg)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(arg->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(arg, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(arg, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(arg, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			arg->cmd_buf_type = CMD_NORM;
		}
		*buf_p = p;
		return (_strlen(p));
	}
	*buf_p = buf;
	return (r);
}

/**
 * read_buf - reads a buffer
 * @arg: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(arg_t *arg, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(arg->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - gets the next line of input from STDIN
 * @arg: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(arg_t *arg, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;
	r = read_buf(arg, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = realloc(p, s + k);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		strncat(new_p, buf + i, k - i);
	else
		strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

