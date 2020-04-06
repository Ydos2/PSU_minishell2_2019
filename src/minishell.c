/*
** EPITECH PROJECT, 2020
** minishell
** File description:
** minishell
*/

#include "minishell.h"

int initialise_minishell(mini_t *mini, char **envp)
{
    signal(SIGINT, set_signal_Handler);
    mini->envp = envp;

    while (1) {
        initialise_shell(mini);
        if (mini->quit != 0)
            break;
        mini->nbr_pipe = 1;
    }
    return (0);
}

int get_argument(mini_t *mini, char *line)
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
    set_other_command(mini, line, mini->envp, space);
    return (0);
}

int loop_pipe(mini_t *mini, char **line, int i)
{
    if (mini->separator[i] == '|')
        get_pipe_arguments(mini, line[i]);
    else if (mini->separator[i] == '>' || mini->separator[i] == '<') {
        get_dup_arguments(mini, line[i]);
        return (1);
    } else
        get_argument(mini, line[i]);
    free(line[i]);
    return (0);
}

int initialise_shell(mini_t *mini)
{
    char *line = NULL;
    size_t len = 0;
    int get = 0;
    char **pipe_line = NULL;

    write(1, "▀▄▀▄▀▄ Minishell ▄▀▄▀▄▀$> ", 50);
    get = getline(&line, &len, stdin);
    if (get == -1) {
        write(1, "\n", 1);
        mini->quit = 1;
        free(line);
        return (0);
    } else if (get < -1) {
        free(line);
        return (0);
    }
    pipe_line = verif_pipe(mini, line);
    for (int i = 0; i < mini->nbr_pipe; i++)
        i += loop_pipe(mini, pipe_line, i);
    return (0);
}