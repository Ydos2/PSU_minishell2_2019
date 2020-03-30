/*
** EPITECH PROJECT, 2019
** main
** File description:
** main
*/

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    mini_t *mini = NULL;
    int quit_val = 0;

    if (argc != 1 && argv)
        return (84);
    mini = initialise_var_start(mini);
    if (initialise_minishell(mini, envp) == 84)
        return (84);
    write(1, "exit\n", 5);
    if (mini->flag != NULL)
        my_free_array(mini->flag);
    quit_val = mini->ret_nbr;
    free(mini);
    return (quit_val);
}

void my_free_array(char **array)
{
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}