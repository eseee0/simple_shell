#include "shell.h"

/**
 * _eputs - to print input string
 * @str: string
 *
 * Return: null
 */

void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		write(2, &str[i], 1);
		i++;
	}
}

/**
 * _eputchar - to write c to stderr
 * @c: character c
 *
 * Return: 1 (Sucess), else -1
 */

int _eputchar(char c)
{
	return (write(2, &c, 1));
}

/**
 * _putfd - to write c to given fd
 * @c: character c
 * @fd: file descriptor
 *
 * Return: 1 (Success), else -1
 */

int _putfd(char c, int fd)
{
	return (write(fd, &c, 1));
}

/**
 * _putsfd - to write string to fd
 * @str: string
 * @fd: file descriptor
 *
 * Return: the number of characters written
 */

int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);

	for (i = 0; str[i] != '\0'; i++)
	{
		if (write(fd, &str[i], 1) == -1)
			return (-1);
	}
	return (i);
}
