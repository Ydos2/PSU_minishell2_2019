/*
** EPITECH PROJECT, 2020
** line_formatting
** File description:
** line_formatting
*/

#include "minishell.h"

int set_line_formatting(char *line)
{
    int space = 0;

    if (line == NULL)
        return (0);
    for (; line[space] != '\0'; space++)
        if (line[space] != ' ')
            break;
    return (space);
}