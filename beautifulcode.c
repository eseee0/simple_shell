#include <stdio.h>

/**
 * main - program that prints the sum of even numbers less than 10
 *
 * Return: always 0
 */

int main(void)
{
	int a;
	int sum = 0;

	for (a = 0; a < 10; a++)
	{
		if (a % 2 == 0)
		{
			sum += a;
		}

	}
printf("sum: %d\n", sum);
return (0);
}
