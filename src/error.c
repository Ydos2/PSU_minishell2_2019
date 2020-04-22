/*
** EPITECH PROJECT, 2020
** error
** File description:
** error
*/

#include "minishell.h"

static void my_error(char c)
{
    write(2, &c, 1);
}

static int my_put_error(char const *str)
{
    int i = 0;

    for (; str[i] != '\0'; i++)
        my_error(str[i]);
    return (0);
}

void error_manager(int arg)
{
    if (WIFSIGNALED(arg)) {
        switch (WTERMSIG(arg)) {
            case 11:
                write(2, "Segmentation fault", 18);
                break;
            case 8:
                write(2, "Floating exception", 18);
                break;
        }
    if (WTERMSIG(arg) != 11 && WTERMSIG(arg) != 8)
        my_put_error(strsignal(WTERMSIG(arg)));
    if (WCOREDUMP(arg))
        write(2, " (core dumped)", 14);
    write(1, "\n", 1);
    }
}