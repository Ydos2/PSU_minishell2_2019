/*
** EPITECH PROJECT, 2020
** pipe
** File description:
** pipe
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "minishell.h"

static void end_tube(int arg, int tube[2])
{
    for (int i = 0; i < 2; i++)
        close(tube[i]);
    for (int i = 0; i < 2; i++)
        wait(&arg);
    error_manager(arg);
}

static void set_tube(mini_t *mini, char *path, char *path_2)
{
    int tube[2];
    int arg;
    pid_t pid_child;
    pid_t pid_parent;

    pipe(tube);
    pid_child = fork();
    if (pid_child == 0) {
        close(tube[1]);
        dup2(tube[0], 0);
        if (execve(path_2, mini->flag_2, mini->envp) == -1)
            exit(0);
    } else if ((pid_parent = fork()
        ) == 0) {
        close(tube[0]);
        dup2(tube[1], 1);
        if (execve(path, mini->flag, mini->envp) == -1)
            exit(0);
    }
    end_tube(arg, tube);
}

static void set_command_pipe(mini_t *mini, char *line, char *line_2, int space)
{
    char *path = NULL;
    char *path_2 = NULL;

    mini->space = space;
    if (line[space+0] != '\0') {
        mini->flag = my_str_to_word_array(line);
        mini->flag_2 = my_str_to_word_array(line_2);

        line = get_unix_arg(mini, line);
        line_2 = get_unix_arg_two(mini, line_2);
        path = set_path(line, mini->envp, mini);
        path_2 = set_path(line_2, mini->envp, mini);
        if (path != NULL && path_2 != NULL)
            set_tube(mini, path, path_2);
        else
            set_command_not_find(line);
    }
}

int get_pipe_arguments(mini_t *mini, char *line, char *line_2)
{
    int i = 0;
    int space = set_line_formatting(line);
    mini->space_2 = set_line_formatting(line_2);

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
    set_command_pipe(mini, line, line_2, space);
    return (0);
}