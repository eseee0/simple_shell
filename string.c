#include "shell.h"

/**
 * starts_with - to check if needle starts with haystack
 * @haystack: string to check
 * @needle: substring to find
 *
 * Return: pointer to the position in haystack where needle starts,
 * or NULL if needle is not found at the beginning of haystack
 */

char *starts_with(const char *haystack, const char *needle)
{
	while (*needle != '\0')
	{
		if (*needle != *haystack)
			return (NULL);
		needle++;
		haystack++;
	}
	return ((char *) haystack);
}

/**
 * _strcat - concatenates two strings
 * @dest: destination buffer
 * @src: source buffer
 *
 * Return: pointer to @dest
 */

char *_strcat(char *dest, const char *src)
{
	char *ptr = dest;

	while (*ptr != '\0')
		ptr++;
	if (src == NULL)
		return (NULL);

	while (*src != '\0')
	{
		*ptr = *src;
		ptr++;
		src++;
	}
	*ptr = '\0';

	return (dest);
}

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
