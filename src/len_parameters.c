/*
** EPITECH PROJECT, 2020
** len_parameters
** File description:
** len_parameters
*/

#include "minishell.h"

static char **malloc_separator(mini_t *mini, char *line, char **pipe_line)
{
    for (int i = 0, j = 0; line[i] != '\0'; i++, j++)
        if (line[i] == ';' || line[i] == '|' || (line[i] == '<'
        && line[i-1] != '<') || (line[i] == '>' && line[i-1] != '>'))
            mini->nbr_pipe += 1;
    mini->separator = malloc(sizeof(char) * mini->nbr_pipe);
    mini->separator_double = malloc(sizeof(char) * mini->nbr_pipe);
    pipe_line = malloc(sizeof(char *) * mini->nbr_pipe);
    return (pipe_line);
}

char **malloc_pipe(mini_t *mini, char *line, char **pipe_line)
{
    int m = 0, k = 0;

    pipe_line = malloc_separator(mini, line, pipe_line);
    for (int i = 0, j = 0; line[i] != '\0'; i++, m++, j = 0) {
        if (line[i] == ';' || line[i] == '|' || (line[i] == '<'
        && line[i-1] != '<') || (line[i] == '>' && line[i-1] != '>')) {
            mini->separator[k] = line[i];
            pipe_line[k] = malloc(sizeof(char) * m);
            m = -1;
            k++;
            j = 1;
        }
        if (j == 1 && ((line[i] == '<' && line[i + 1] == '<') ||
            (line[i] == '>' && line[i + 1] == '>')))
            mini->separator_double[k - 1] = line[i];
        else if (j == 1)
            mini->separator_double[k - 1] = '0';
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
        } else if (line[i] != '<' && line[i] != '>')
            pipe_line[k][j] = line[i];
        else
            j--;
    }
    return pipe_line;
}