#include "shell.h"

/**
 * _getenv - gets the value of a specified environment variable
 * @key: variable to use for
 *
 * Return: pointer to start index of the value
 */

char *_getenv(char *key)
{
        extern char **environ;
        char **ptr = environ;
        size_t namelen = _strlen(key);

        while (*ptr)
        {
                if (_strcmp(*ptr, key, namelen) == 0 && (*ptr) [namelen] == '=')
                        return (&((*ptr)[namelen + 1]));
        ptr++;
        }
        return (NULL);
}


size_t _strlen(const char *str)
{
        size_t len = 0;
        while (*str != '\0')
        {
                len++;
                str++;
        }
        return (len);
}


int _strcmp(const char *s1, const char *s2, size_t n)
{
        while (n > 0 && *s1 == *s2)
        {
                n--;
                s1++;
                s2++;
        }

        if (n == 0)
        {
                return (0);
        }
        else
        {
                return (*s1 - *s2);
        }
}
