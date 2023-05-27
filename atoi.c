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
