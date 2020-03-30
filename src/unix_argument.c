/*
** EPITECH PROJECT, 2020
** unix_argument
** File description:
** unix_argument
*/

#include "minishell.h"

int set_unix(mini_t *mini, char *path, char **envp)
{
    pid_t pid = 0;
    int arg = 0;

    pid = fork();
    if (pid == 0)
        execve(path, mini->flag, envp);
    else if (pid > 0)
        waitpid(pid, &arg, 0);
    if (WIFSIGNALED(arg))
        my_putstr(strsignal(WTERMSIG(arg)));
    kill(pid, SIGKILL);
    return (0);
}

char *get_unix_arg(mini_t *mini, char *line)
{
    char *arg_line = NULL;
    int i = 0;
    int j = 0;

    for (int k = mini->space; line[k] != '\0'; k++, i++);
    arg_line = malloc(sizeof(char) * i);
    for (int k = mini->space; j != i; j++, k++) {
        if (line[k] == ' ')
            break;
        arg_line[j] = line[k];
    }
    return (arg_line);
}