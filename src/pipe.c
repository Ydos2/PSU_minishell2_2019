/*
** EPITECH PROJECT, 2020
** pipe
** File description:
** pipe
*/

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "minishell.h"

static void fils(int out, char *path_2, mini_t *mini)
{
    close(STDOUT_FILENO);
    dup(out);
    close(STDERR_FILENO);
    dup(out);
    close(out);
    if (execve(path_2, mini->flag_2, mini->envp) == -1)
        exit(0);
}

static void second_fork(int tube[2], mini_t *mini, char *path, char **envp)
{
    pid_t pid;
    int arg = 0;

    pid = fork();
    if (pid == 0) {
        close(tube[1]);
        close(STDIN_FILENO);
        dup(tube[0]);
        close(tube[0]);
        execve(path, mini->flag, envp);
    }
    waitpid(pid, &arg, 0);
    kill(pid, SIGKILL);
}

static int set_tube(mini_t *mini, char *path, char *path_2, char **envp)
{
    int tube[2];
    pid_t pid;
    int arg = 0;

    if (pipe(tube) == -1)
        return (0);
    pid = fork();
    if (pid == 0) {
        close(tube[0]);
        fils(tube[1], path_2, mini);
    } else {
        waitpid(pid, &arg, 0);
        error_manager(arg);
        kill(pid, SIGKILL);
        second_fork(tube, mini, path, envp);
    }
    return (0);
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
        path = set_path(line, mini->envp, mini);
        path_2 = set_path(line_2, mini->envp, mini);
        if (path != NULL)
            set_tube(mini, path, path_2, mini->envp);
        else
            set_command_not_find(line);
    }
}

int get_pipe_arguments(mini_t *mini, char *line, char *line_2)
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
    set_command_pipe(mini, line, line_2, space);
    return (0);
}