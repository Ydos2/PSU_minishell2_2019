/*
** EPITECH PROJECT, 2020
** my_malloc_array
** File description:
** my_malloc_array
*/

#include "minishell.h"

char **my_malloc_array(int x, int y)
{
    char **array = (char **) malloc(sizeof(char *) * x);
    for (int i = 0; i < x; i++)
        array[i] = (char *) malloc(sizeof(char) * y);

    return array;
}