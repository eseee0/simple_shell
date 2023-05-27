#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define MAX_ARGS 200
#define MAX_COMMAND 200

#define BUFFER_SIZE 1024

extern char **environ;

/**
 * struct liststr - for singly linked list
 * @num: number
 * @str: string
 * @next: pointer to next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passarg - allows a uniform prototype for function pointer struct
 * @env: linked list representing the local copy of environ
 * @envp:  pointer to the first element of the array of pointers to env vars
 * @history: history node
 * @alias: alias node
 * @arg_get: string containing arguments generated from getline
 * @argv: array of strings generated from arg
 * @path: the current command's string path
 * @fname: filename of the program
 * @environ: copy of environ obtained from LL env
 * @argc: argument count
 * @err_num: error code for shell_exit
 * @linecount_flag: indicates whether to count this line of input
 * @env_changed: indicates if environ was changed
 * @status: status of return for the last executed command
 * @line_count: count of lines
 * @readfd: file descriptor from which to read line input
 * @histcount: the count of history line numbers
 * @cmd_buf: the address of pointer to cmd_buf, checks if chaining is required
 * @cmd_buf_type: CMD_type (&&, ||, ;)
 */

typedef struct passarg
{
	list_t *env;
	list_t *history;
	list_t *alias;
	char *arg_get;
	char **argv;
	char **envp;
	char *path;
	char *fname;
	char **environ;
	int argc;
	int err_num;
	int linecount_flag;
	int env_changed;
	int status;
	unsigned int line_count;

	int readfd;
	int histcount;
	char **cmd_buf;
	int cmd_buf_type;
} arg_t;

void shell_prompt(char **av, char **env);
int _execute(char *cmd, char **argv);
void handle_path(char *cmd);
bool check_file_status(char *pathname);

char *_getenv(char *key);
size_t _strlen(const char *str);
int _strcmp(const char *s1, const char *s2, size_t n);

int exit_shell(arg_t *arg);

int _atoi(char *str);

int _env(arg_t *arg);

char *get_env(arg_t *arg, const char *name);
int unset_env(arg_t *arg);
int set_env(arg_t *arg);

void _eputs(char *str);
int _eputchar(char c);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

char *starts_with(const char *haystack, const char *needle);
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, const char *src);
char *_strdup(char *str);

int main(int argc, char **argv, char **env);

int _cd(arg_t *arg);


#endif
