/*
** EPITECH PROJECT, 2020
** simple_left
** File description:
** simple_left
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "minishell.h"

static int set_unix_dup(mini_t *mini, char *path, char *path_2, char **envp)
{
    pid_t pid = 0;
    int arg = 0;
    int out = open(path_2, O_RDONLY, 0);

    pid = fork();
    if (pid == 0) {
        dup2(out, 1);
        close(out);
        execve(path, mini->flag, envp);
    } else if (pid > 0)
        waitpid(pid, &arg, 0);
    error_manager(arg);
    kill(pid, SIGKILL);
    return (0);
}

static void set_command_dup(mini_t *mini, char *line, char *line_2, int space)
{
    char *path = NULL;
    char *path_2 = NULL;

    mini->space = space;
    if (line[space+0] != '\0') {
        mini->flag = my_str_to_word_array(line);
        line = get_unix_arg(mini, line);
        path = set_path(line, mini->envp, mini);
        path_2 = parssing_path(line_2);
        if (path != NULL)
            set_unix_dup(mini, path, path_2, mini->envp);
        else if (access(line, F_OK) == 0)
            set_unix_dup(mini, line, line_2, mini->envp);
        else
            set_command_not_find(line);
    }
}

int get_left_arguments(mini_t *mini, char *line, char *line_2)
{
    int i = 0;
    int space = set_line_formatting(line);

    if (my_strncmp(line, "./", 2, space) == 0)
        i = set_ex(mini, line, space);
    if (my_strncmp(line, "exit", 4, space) == 0)
        i = set_exit(mini, line);
    if (my_strncmp(line, "cd", 2, space) == 0)
        i = initialise_cd(line, mini->envp, mini);
    if (my_strncmp(line, "setenv", 6, space) == 0)
        i = initialise_setenvv(line, mini);
    if (my_strncmp(line, "unsetenv", 8, space) == 0)
        i = initialise_unsetenvv(line, mini->envp, mini);
    if (my_strncmp(line, "env", 3, space) == 0)
        i = initialise_envv(mini->envp, line);
    if (i == 1)
        return (0);
    set_command_dup(mini, line, line_2, space);
    return (0);
}