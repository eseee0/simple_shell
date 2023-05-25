#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(char *s)
{
  int i = 0;

  if (!s) {
    return (0);
  }

  while (s[i] != '\0') {
    i++;
  }

  return (i);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @s1: the first strang
 * @s2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
  while (*s1 != '\0' && *s2 != '\0') {
    if (*s1 != *s2) {
      return (*s1 - *s2);
    }
    s1++;
    s2++;
  }

  if (*s1 == '\0' && *s2 == '\0') {
    return (0);
  } else if (*s1 == '\0') {
    return (-1);
  } else {
    return (1);
  }
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
  int i = 0;

  while (needle[i] != '\0') {
    if (haystack[i] != needle[i]) {
      return (NULL);
    }
    i++;
  }

  return ((char *)haystack + i);
}

/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
  int i = _strlen(dest);

  while (*src != '\0') {
    dest[i++] = *src++;
  }

  dest[i] = '\0';

  return (dest);
}
