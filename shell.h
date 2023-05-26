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

void shell_prompt(char **av, char **env);
void prompt(char **av);
char *_getenv(char *key);
size_t _strlen(const char *str);
int _strncmp(const char *s1, const char *s2, size_t n);

#endif
