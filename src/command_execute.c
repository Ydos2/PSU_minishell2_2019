/*
** EPITECH PROJECT, 2020
** command_execute
** File description:
** command_execute
*/

#include "minishell.h"

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