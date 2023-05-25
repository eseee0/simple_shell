#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(arg_t *arg, char *path)
{
  struct stat st;

  (void)arg;
  if (!path || stat(path, &st)) {
    return (0);
  }

  if (S_ISREG(st.st_mode)) {
    return (1);
  }
  return (0);
}

/**
 * dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
  static char buf[1024];
  int i = 0, k = 0;

  for (k = 0, i = start; i < stop; i++) {
    if (pathstr[i] != ':') {
      buf[k++] = pathstr[i];
    }
  }
  buf[k] = 0;
  return (buf);
}

/**
 * find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(arg_t *arg, char *pathstr, char *cmd)
{
  char *full_path = NULL;
  char *p;

  for (p = strtok(pathstr, ":"); p; p = strtok(NULL, ":")) {
    full_path = calloc(strlen(p) + strlen(cmd) + 2, sizeof(char));
    if (!full_path) {
      return (NULL);
    }
    strcpy(full_path, p);
    strcat(full_path, "/");
    strcat(full_path, cmd);
    if (is_cmd((struct passarg *)arg, full_path)) {
      arg->path = full_path;
      return (full_path);
    }
    free(full_path);
  }

  return (NULL);
}
