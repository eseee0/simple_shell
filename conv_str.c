#include "shell.h"

/**
 * _atoi - to convert string to integer
 * @str: string
 *
 * Return: 0 if true, else 0
 */

int _atoi(char *str)
{
        int result = 0;
        int i;

        for (i = 0; str[i] != '\0'; i++)
        {
                if (str[i] >= '0' && str[i] <= '9')
                {
                        result *= 10;
                        result += str[i] - '0';
                }
                else if (str[i] == '-')
                        result *= -1;
        }
        return (result);
}

/**
 * is_interactive - to check if shell is in interactive mode
 * @arg: information
 *
 * Return: 1 if true, else 0
 */

int is_interactive(arg_t *arg)
{
        return (isatty(STDIN_FILENO) && arg->readfd <= 2);
}



/**
 * is_alpha - to check for alphabet in character
 * @c: character
 *
 * Return: 1 if true, else 0
 */

int is_alpha(int c)
{
        if (c >= 'a' && c <= 'z')
                return (1);
        if (c >= 'A' && c <= 'Z')
                return (1);
        return (0);
}

/**
 * is_delimiter - to check for delimeter in character
 * @delim: delimeter string
 * @c: character
 *
 * Return: 1 if true, else 0
 */

int is_delimiter(char c, char *delim)
{
        char *d = delim;

        while (*d)
        {
                if (*d == c)
                        return (1);
        }
        return (0);
}
