#include "shell.h"

/**
 * _strcpy - to copy string
 * @dest: destination buffer
 * @src: source string
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest, const char *src)
{
	char *dest_ptr = dest;

	if (dest == src || src == NULL)
		return (dest);

	while ((*dest_ptr++ = *src++))
		;

	return (dest);
}

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */

char *_strdup(char *str)
{
	int length = _strlen(str); 
	char *ret;
	
	ret = malloc(length + 1);

	if (ret == NULL)
		return (NULL);
	_strcpy(ret, str);
	return (ret);
	if (str != NULL)
		free(str);
}


/**
 * _puts - to print input string
 * @str: string
 *
 * Return: null
 */

void _puts(const char *str)
{
	if (str == NULL)
		return;
	while (*str != '\0')
	{
		putchar(*str);
		str++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _putchar(char c)
{
	static char buf[WRITE_BUF_SIZE];
	static int i = 0;

	if (i >= WRITE_BUF_SIZE || c == BUF_FLUSH)
	{
		write(1, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
		buf[i++] = c;

	return (1);
}
