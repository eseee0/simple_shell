#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */

int main(int ac, char **av)
{
	arg_t arg;
	int fd = 0;

	if (ac == 2)
		fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		if (errno == EACCES)
			exit(126);
		else if (errno == ENOENT)
		{
			_eputs(av[0]);
			_eputs(": 0: Can't open ");
			_eputs(av[1]);
			_eputs((char *) '\n');
			_eputchar(BUF_FLUSH);
			exit(127);
		}
		else
			return (EXIT_FAILURE);
	}
	arg.readfd = fd;
/**
 * if (populate_env_list(&arg) != 0)
 * return (EXIT_FAILURE);
*/
	if (read_history(&arg) != 0)
		return (EXIT_FAILURE);
	if (hsh(&arg, av) != 0)
		return (EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
