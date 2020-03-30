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
    }
    return (0);
}

int initialise_shell(mini_t *mini)
{
    char *line = NULL;
    size_t len = 0;
    int get = 0;

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
    line = my_len_str(line);
    get_argument(mini, line);
    free(line);
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

void set_other_command(mini_t *mini, char *line, char **envp, int space)
{
    char *path = NULL;

    mini->space = space;
    if (line[space+0] != '\0') {
        mini->flag = my_str_to_word_array(line);
        line = get_unix_arg(mini, line);
        path = set_path(line, envp, mini);
        if (path != NULL)
            set_unix(mini, path, envp);
        else
            set_command_not_find(line);
    }
}

void set_command_not_find(char *line)
{
    my_putstr(line);
    write(1, ": Command not found.\n", 21);
}