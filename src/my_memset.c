/*
** EPITECH PROJECT, 2020
** my_memset
** File description:
** my_memset
*/

#include "minishell.h"

void my_memset(char *buffer, int size)
{
    int i = 0;

    while (i < size) {
        buffer[i] = '\0';
        i++;
    }
}