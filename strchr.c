#include "shell.h"

/**
 * _strchr - Locates the first occurrence of a character in a string
 * @str: The string to search
 * @c: The character to locate
 *
 * Return: If the character is found, returns a pointer to the first occurrence
 *         of the character in the string. If the character is not found,
 *         returns NULL.
 */
char *_strchr(const char *str, int c)
{
	while (*str != '\0')
	{
		if (*str == c)
			return ((char *)str);
		str++;
	}
	return (NULL);
}

