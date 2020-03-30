/*
** EPITECH PROJECT, 2020
** clear_str
** File description:
** clear_str
*/

#include "minishell.h"

char *my_clear_begin(char *str)
{
    int i = 0;

    for (; str && str[i]; i++)
        if (str[i] != ' ')
            return &str[i];
    return (str);
}

char *my_clear_space(char *str)
{
    int i = 0;
    int j = 0;
    int spaced = 0;
    char *clear = malloc(sizeof(char) * my_strlen(str) + 1);

    while (str && str[i]) {
        if (str[i] != ' ') {
            clear[j] = str[i];
            j++;
            spaced = 0;
        } else if (spaced == 0 && str[i] == ' ') {
            spaced = 1;
            clear[j] = ' ';
            j++;
        }
        i++;
    }
    clear[j] = '\0';
    return (clear);
}

char *my_clear_str(char *str)
{
    int i = 0;
    char *clear;

    while (str && str[i]) {
        if (str[i] == '\t')
            str[i] = ' ';
        i++;
    }
    str = my_clear_begin(str);
    clear = my_clear_space(str);
    return (clear);
}

int my_strlen(char const *str)
{
    int i = 0;

    if (str == NULL)
        return (0);
    for (; str[i] != '\0'; i++);
    return (i);
}