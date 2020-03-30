/*
** EPITECH PROJECT, 2020
** my_puterror
** File description:
** my_puterror
*/

#include "minishell.h"

int my_puterror(char const *str)
{
    int i = 0;

    for (; str[i] != '\0'; i++)
        my_putchar_error(str[i]);
    return (0);
}

void my_putchar_error(char c)
{
    write(2, &c, 1);
}