/*
** EPITECH PROJECT, 2020
** pipe
** File description:
** pipe
*/

#include "minishell.h"

int get_pipe_arguments(mini_t *mini, char *line)
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