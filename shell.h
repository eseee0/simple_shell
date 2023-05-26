#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define MAX_COMMAND 20

#define CMD_NORM	0
#define CMD_AND		2
#define CMD_CHAIN	3
#define CMD_OR		1

#define BUF_FLUSH -1
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024

#define USE_STRTOK 0
#define USE_GETLINE 0

#define CONVERT_UNSIGNED	2
#define CONVERT_LOWERCASE	1


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
 * @cmd_buf: the address of pointer to cmd_buf, indicates if chaining is required
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

#define ARG_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - it has builtin string
 * @type: command flag
 * @func: function
 */
typedef struct builtin
{
	char *type;
	int (*func)(arg_t *);
} builtin_table;


/* builtin_func1.c */
int _hist(arg_t *arg);
int alias_unset(arg_t *arg, char *str);
int alias_set(arg_t *arg, char *str);
int alias_print(list_t *node);
int _alias(arg_t *arg);

/* builtin_func2.c */
int _cd(arg_t *arg);
int exit_shell(arg_t *arg);
int _help(arg_t *arg);

/* conv_str.c */
int _atoi(char *str);
int is_interactive(arg_t *arg);
int is_alpha(int c);
int is_delimiter(char c, char *delim);

/* env.c */
int _env(arg_t *arg);
char *get_env(arg_t *arg, const char *name);
int unset_env(arg_t *arg);
int set_env(arg_t *arg);
int pop_env_list(arg_t *arg);

/* error_func1.c */
void _eputs(char *str);
int _eputchar(char c);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* error_func2.c */
int _erratoi(char *str);
void print_error(arg_t *arg, char *errstr);
int print_dec(int input, int fd);
char *conv_num(long int num, int base, int flags);
void rem_comments(char *ptr);

/* simple_shell.c */
int shell(int ac, char **av);
int hsh(arg_t *arg);

/* str1.c */
char *_strcpy(char *dest, const char *src);
char *_strdup(char *str);
void _puts(const char *str);
int _putchar(char c);

/* str2.c */
int _strlen(char *str);
int _strcmp(const char *str1, const char *str2);
char *starts_with(const char *haystack, const char *needle);
char *_strcat(char *dest, const char *src);

/* list_func1.c */
list_t *add_node(list_t **head, const char *str, int num);
list_t *add_node_end(list_t **head, char *str, int num);
void free_list(list_t *head);
int print_list_str(list_t *head);
int del_node_index(list_t **head, unsigned int index);

/* list_func2.c */
size_t list_len(const list_t *h);
char **list_to_strings(list_t *head);
size_t print_list(const list_t *h);
list_t *node_starts_with(list_t *node, char *prefix, char c);
ssize_t get_node_index(list_t *head, char *str);

/* strstr.c */
char *_strchr(const char *str, int c);

/* prompt.c */
int main(int argc, char **argv);

/* getarg.c */
void clear_arg(arg_t *arg);
void set_arg(arg_t *arg, char **av);
void free_arg(arg_t *arg, int all);
int replace_alias(arg_t *arg);
int replace_vars(arg_t *arg);
int replace_string(char **old, char *new);

#endif
