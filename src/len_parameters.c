/*
** EPITECH PROJECT, 2020
** len_parameters
** File description:
** len_parameters
*/

#include "minishell.h"

char **malloc_pipe(mini_t *mini, char *line, char **pipe_line)
{
    int m = 0;
    int k = 0;

    for (int i = 0, j = 0; line[i] != '\0'; i++, j++)
        if (line[i] == ';' || line[i] == '|' || (line[i] == '<'
        && line[i-1] != '<') || (line[i] == '>' && line[i-1] != '>'))
            mini->nbr_pipe += 1;
    mini->separator = malloc(sizeof(char) * mini->nbr_pipe);
    pipe_line = malloc(sizeof(char *) * mini->nbr_pipe);
    for (int i = 0; line[i] != '\0'; i++, m++)
        if (line[i] == ';' || line[i] == '|' || (line[i] == '<'
        && line[i-1] != '<') || (line[i] == '>' && line[i-1] != '>')) {
            mini->separator[k] = line[i];
            pipe_line[k] = malloc(sizeof(char) * m);
            m = -1;
            k++;
        }
    pipe_line[k] = malloc(sizeof(char) * m);
    return pipe_line;
}

char **verif_pipe(mini_t *mini, char *line)
{
    char **pipe_line = NULL;

    line = my_len_str(line);
    pipe_line = malloc_pipe(mini, line, pipe_line);
    for (int i = 0, j = 0, k = 0; line[i] != '\0'; i++, j++) {
        if (line[i] == ';' || line[i] == '|' || (line[i] == '<'
        && line[i-1] != '<') || (line[i] == '>' && line[i-1] != '>')) {
            j = -1;
            k++;
        } else
            pipe_line[k][j] = line[i];
    }
    return pipe_line;
}