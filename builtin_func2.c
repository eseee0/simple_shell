#include "shell.h"

/**
 * _cd - to change current directory
 * @arg: information
 *
 * Return: 0
 */

int _cd(arg_t *arg)
{
        if (_strcmp(arg->argv[0], "cd") == 0)
        {
                if (arg->argv[1])
                {
                        if (chdir(arg->argv[1]) != 0)
                        {
                                write(STDERR_FILENO, "Could not change directory to '%s'\n", (size_t)arg->argv[1]);
                                return (1);
                        }
                        else
                                chdir(getenv("HOME"));
                }
        }
        return (0);
}

/**
 * exit_shell - to exit the shell
 * @arg: information about function
 *
 * Return: exit status
 */

int exit_shell(arg_t *arg)
{
        if (_strcmp(arg->argv[0], "exit") == 0)
        {
                if (arg->argv[1])
                {
                        int exit_status = _atoi(arg->argv[1]);
                        if (exit_status < 0)
                        {
                                write(STDERR_FILENO, "Illegal number: %d\n", exit_status);
                                return (1);
                        }
                        write(STDOUT_FILENO, "exit\n", 5);
                        exit(exit_status);
                }
                else
                {
                        write(STDOUT_FILENO, "exit\n", 5);
                        exit(0);
                }
        }
        return (0);
}


/**
 * _help - help function
 * @arg: information
 *
 * Return: 0
 */

int _help(arg_t *arg)
{
        if (_strcmp(arg->argv[0], "help") == 0)
        {
                write(STDOUT_FILENO, "Available commands:\n", 20);
                write(STDOUT_FILENO, "  exit\n", 5);
                write(STDOUT_FILENO, "  cd\n", 4);
                write(STDOUT_FILENO, "  help\n", 5);
        }
        return (0);
}

