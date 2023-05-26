#include "shell.h"

bool check_file_status(char *pathname)
{
        int stat_return;
        struct stat stat_buf;

        stat_return = stat(pathname, &stat_buf);

        if (stat_return == 0)
        {
                if (S_ISREG(stat_buf.st_mode) == 0)
                        return (false);

                if (access(pathname, X_OK) == 0)
                        return (true);

                return (false);
        }

        return (false);
}

void handle_path(char *command)
{
        char *path = getenv("PATH");
        char *dir;
        char *get_path;

        for (dir = strtok(path, ":"); dir != NULL;)
        {
                get_path = malloc(strlen(dir) + strlen(command) + 2);
                sprintf(get_path, "%s/%s", dir, command);

                if (access(get_path, F_OK) != -1)
                {
                        /* _execute(get_path); */
                        return;
                }

                free(get_path);
        }

        printf("Command not found\n");
}

int _execute(char *command, char **argv)
{
        extern char **environ;

        pid_t pid = fork();

        if (pid == 0)
        {
                execve(command, argv,  environ);
                perror("execve");
                exit(EXIT_FAILURE);
        }
        else if (pid < 0)
        {
                perror("fork");
                exit(EXIT_FAILURE);
        }
        wait(NULL);
        return (0);

}

void shell_prompt(char **av, char **env)
{
        char *buff = NULL;
        int i, j, status;
        size_t buffsize = 0;
        ssize_t num_char;
        pid_t wpid;


        while (1)
        {
                if (isatty(STDIN_FILENO))
                        printf("$ ");

                num_char = getline(&buff, &buffsize, stdin);
                if (num_char == -1)
                {
                        free(buff);
                        exit(EXIT_FAILURE);
                }
                i = 0;
                while (buff[i])
                {
                        if (buff[i] == '\n')
                                buff[i] = 0;
                        i++;
                }

                j = 0;
                av[j] = strtok(buff, " "); /* or use argv[0] */
                while (av[j] != NULL) /* can remove "!= NULL" */
                {
                        j++;
                        av[j] = strtok(NULL, " "); /* delete j++ and do argv[++j] = strtok(NULL, " "); for reduced lines */
                }
                wpid = fork();
                if (wpid == -1)
                {
                        free(buff);
                        exit(EXIT_FAILURE);
                }
                if (wpid == 0)
                {
                        if (execve(av[0], av, env) == -1)
                                printf("%s: No such file or directory\n", av[0]);

                }
                else
                        wait(&status);
        }
}
