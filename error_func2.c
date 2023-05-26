#include "shell.h"

/**
 * _erratoi - to convert string to integer
 * @str: string
 *
 * Return: 0 if there are no numbers, else -1
 */

int _erratoi(char *str)
{
        int i = 0;
        unsigned long int result = 0;

	if (*str == '+')
    		str++;

	while (str[i] != '\0')
	{
    		if (str[i] >= '0' && str[i] <= '9')
		{
			result *= 10;
			result += (str[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	i++;
	return ((int)result);
}


/**
 * print_error - to print error message
 * @arg: strucr information
 * @errstr: error string
 *
 * Return: 0 if there are no numbers, else -1
 *
 */

void print_error(arg_t *arg, char *errstr)
{
        write(STDERR_FILENO, arg->fname, _strlen(arg->fname));
        write(STDERR_FILENO, ": ", 2);
        print_dec(arg->line_count, STDERR_FILENO);
        write(STDERR_FILENO, ": ", 2);
        write(STDERR_FILENO, arg->argv[0], _strlen(arg->argv[0]));
        write(STDERR_FILENO, ": ", 2);
        write(STDERR_FILENO, errstr, _strlen(errstr));
}

/**
 * print_dec - to print decimal
 * @input: input
 * @fd: file descriptor
 *
 * Return: character count
 */

int print_dec(int input, int fd)
{
	int count = 0;
	char *digits = "0123456789";

	if (fd == STDERR_FILENO)
	{
		_putchar('-');
		count++;
	}

	if (input < 0)
		input = -input;
	while (input > 0)
	{
	_putchar(digits[input % 10]);
	input /= 10;
	count++;
	}
	return (count);
}

/**
 * conv_num - convert number
 * @num: number
 * @base: base
 * @flags: flags for argument
 *
 * Return: string
 */

char *conv_num(long int num, int base, int flags)
{
        static char buffer[50];
        char *ptr = &buffer[49];
	static char *array;
        unsigned long n = num;

        if (!(flags & CONVERT_UNSIGNED) && num < 0)
        {
                n = labs(num);
                *ptr-- = '-';
        }

        array = (flags & CONVERT_LOWERCASE) ? "0123456789abcdef" : "0123456789ABCDEF";

        do
        {
                *ptr-- = array[n % base];
                n /= base;
        } while (n != 0);

        return (++ptr);
}


/**
 * rem_comments - to replace first instance of '#' with '\0'
 * @ptr: address of string
 *
 * Return: Always 0
 */

void rem_comments(char *ptr)
{
	int x = 0;

	while (ptr[x] != '\0')
	{
		if (ptr[x] == '#' && (x == 0 || ptr[x - 1] == ' '))
		{
			ptr[x] = '\0';
			break;
		}
		x++;
	}
}


