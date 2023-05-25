#include "shell.h"

/**
 * get_history_file - gets the history file
 * @arg: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_file(arg_t *arg)
{
        char *buf, *dir;

        dir = _getenv(arg, "HOME=");

        if (!dir)
                return (NULL);
        buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
        if (!buf)
                return (NULL);
        _strcpy(buf, dir);
        _strcat(buf, "/");
        _strcat(buf, HIST_FILE);
        free(buf);
        return (buf);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @arg: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(arg_t *arg)
{
  ssize_t fd;
  char *filename = get_history_file(arg);
  list_t *node = arg->history;

  if (!filename) {
    return (-1);
  }

  fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
  if (fd == -1) {
    return (-1);
  }
  while (node) {
    write(fd, node->str, _strlen(node->str));
    write(fd, "\n", 1);
    node = node->next;
  }
  close(fd);
  free(filename);
  return (1);
}

/**
 * read_history - reads history from file
 * @arg: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(arg_t *arg)
{
  int i, last = 0, linecount = 0;
  ssize_t fd, rdlen, fsize = 0;
  struct stat st;
  char *buf = NULL, *filename = get_history_file(arg);

  if (!filename) {
    return (0);
  }

  fd = open(filename, O_RDONLY);
  if (fd == -1) {
    return (0);
  }
  if (!fstat(fd, &st)) {
    fsize = st.st_size;
  }
  if (fsize < 2) {
    return (0);
  }
  buf = malloc(sizeof(char) * (fsize + 1));
  if (!buf) {
    return (0);
  }
  rdlen = read(fd, buf, fsize);
  buf[fsize] = 0;
  if (rdlen <= 0) {
    return (free(buf), 0);
  }
  close(fd);
  for (i = 0; i < fsize; i++) {
    if (buf[i] == '\n') {
      buf[i] = 0;
      add_node_end(&(arg->history), buf + last, linecount++);
      last = i + 1;
    }
  }
  if (last != i) {
    add_node_end(&(arg->history), buf + last, linecount++);
  }
  free(buf);
  arg->histcount = linecount;
  while (arg->histcount-- >= HIST_MAX) {
    delete_node_at_index(&(arg->history), 0);
  }
  renumber_history(arg);
  free(buf);
  free(filename);
  return (arg->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @arg: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */

int build_history_list(arg_t *arg, char *buf, int linecount)
{
  list_t *node = malloc(sizeof(list_t));

  if (!node) {
    return (-1);
  }

  node->str = buf;
  node->num = linecount;
  node->next = NULL;

  if (!arg->history) {
    arg->history = node;
  } else {
    list_t *last = arg->history;
    while (last->next) {
      last = last->next;
    }
    last->next = node;
  }

  return (0);
}


/**
 * renumber_history - renumbers the history linked list after changes
 * @arg: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(arg_t *arg)
{
  list_t *node = arg->history;
  int i = 1;

  while (node) {
    node->num = i++;
    node = node->next;
  }

  return (i - 1);
}
