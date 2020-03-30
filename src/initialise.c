/*
** EPITECH PROJECT, 2020
** initialise
** File description:
** initialise
*/

#include "minishell.h"

mini_t *initialise_var_start(mini_t *mini)
{
    mini = malloc(sizeof(mini_t));
    mini->quit = 0;
    mini->ret_nbr = 0;
    mini->flag = NULL;
    mini->cd_old = NULL;
    mini->cd_new = getcwd(NULL, 0);
    return (mini);
}

int set_exit(mini_t *mini, char *line)
{
    char **flag = my_str_to_word_array(line);
    int nbr = 1;

    if (flag[1] != NULL) {
        nbr = get_exit(flag, nbr);
        if (nbr == -1)
            return (1);
        draw_exit(mini, flag, nbr);
    }
    mini->quit = 1;
    return (1);
}

int get_exit(char **flag, int nbr)
{
    for (int i = 0, j = 0; flag[1][i+1] != '\0'; nbr = nbr * 10, i++, j++) {
        if (flag[1][i] == '-' && j != 0) {
            write(1, "exit: Badly formed number.\n", 27);
            return (-1);
        }
        if ((flag[1][i] < '0' || flag[1][i] > '9') && flag[1][i] != '-') {
            write(1, "exit: Expression Syntax.\n", 25);
            return (-1);
        }
    }
    return (nbr);
}

void draw_exit(mini_t *mini, char **flag, int nbr)
{
    int actu_nbr = 0;

    if (flag[1][0] == '-') {
        for (int i = 1, j = nbr; flag[1][i] != '\0'; i++) {
            actu_nbr = (flag[1][i] - 48) * j;
            mini->ret_nbr += actu_nbr;
            j = j / 10;
        }
        mini->ret_nbr = (mini->ret_nbr * -1) / 10;
    } else {
        for (int i = 0, j = nbr; flag[1][i] != '\0'; i++) {
            actu_nbr = (flag[1][i] - 48) * j;
            mini->ret_nbr += actu_nbr;
            j = j / 10;
        }
    }
}