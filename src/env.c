/*
** EPITECH PROJECT, 2020
** env
** File description:
** env
*/

#include "minishell.h"

char *set_path(char *line, char **envp, mini_t *mini)
{
    char *path = NULL;

    mini->j = 5;
    if (get_env_path(envp, mini) == 0)
        return (NULL);
    for (int j = 5, k = 0; envp[mini->i][j] != '\0'; j++, k++) {
        if (envp[mini->i][j] == ':') {
            path = set_test_path(envp, line, k, mini);
            k = -1;
        }
        if (path != NULL)
            break;
    }
    return (path);
}

int get_env_path(char **envp, mini_t *mini)
{
    for (mini->i = 0; envp[mini->i] != NULL; mini->i++) {
        if (envp[mini->i][0] == 'P' && envp[mini->i][1] == 'A' &&
        envp[mini->i][2] == 'T' && envp[mini->i][3] == 'H' &&
        envp[mini->i][4] == '=') {
            return (1);
        }
    }
    return (0);
}

char *set_test_path(char **envp, char *line, int k, mini_t *mini)
{
    char *path = NULL;
    int nbr = 0;
    int j = mini->j;
    int e = 0;

    for (nbr = 0; line[nbr] != '\0'; nbr++);
    nbr = nbr + k;
    path = malloc(sizeof(char) * nbr);
    for (; e != k; j++, e++)
        path[e] = envp[mini->i][j];
    path[e] = '/';
    e++;
    for (int y = 0; line[y] != '\0'; y++, e++)
        path[e] = line[y];
    mini->j = mini->j + e-2;
    if (access(path, F_OK) == 0)
        return (path);
    else
        return (NULL);
}

int initialise_envv(char **envp, char *line)
{
    char **array = my_str_to_word_array(line);

    if (array[1] != NULL)
        return (1);
    for (int i = 0; envp[i] != NULL; i++) {
        my_putstr(envp[i]);
        write(1, "\n", 1);
    }
    return (1);
}