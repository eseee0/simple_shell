#include "shell.h"

/**
 * _strlen -  to get length of a string
 * @s: string
 *
 * Return: length of string, len
 */

int _strlen(char *str)
{
	int len = 0;

	while (*str != '\0')
	{
		len++;
		str++;
	}
	return (len);
}


/**
 * _strcmp - to compare two strings
 * @str1: string 1
 * @str2: string 2
 *
 * Return: 0 if the strings are equal, else 1
 */ 

int _strcmp(const char *str1, const char *str2)
{
	int i;

	for (i = 0; str1[i] != '\0' && str2[i] != '\0'; i++)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
	}

	if (str1[i] == '\0' && str2[i] == '\0')
		return (0);
	else if (str1[i] == '\0')
		return (-1);
	else
		return (1);
}

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
