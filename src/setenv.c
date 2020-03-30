/*
** EPITECH PROJECT, 2020
** setenv
** File description:
** setenv
*/

#include "minishell.h"

int initialise_setenvv(char *line, mini_t *mini)
{
    char **array = NULL;

    array = my_str_to_word_array(line);
    if (array[1] == NULL)
        return (initialise_envv(mini->envp, line));
    else if (array[3] != NULL && array[2] != NULL) {
        write(1, "setenv: Too many arguments.\n", 28);
        return (1);
    }
    mini->envp = set_can_i_replace(array[2], mini->envp, array[1]);
    return (1);
}

char *set_copy_str(char *str, char *copy, int *j)
{
    int k = 0;

    while (copy != NULL && copy[k] != '\0') {
        str[*j] = copy[k];
        *j = *j + 1;
        k++;
    }
    return (str);
}

char **set_replace_this(char **env, char *path, char *replace, int *i)
{
    int j = 0;

    env[*i] = malloc(sizeof(char)
    * (my_strlen(path) + 1 + my_strlen(replace) + 1));
    env[*i] = set_copy_str(env[*i], path, &j);
    env[*i][j] = '=';
    j = j + 1;
    env[*i] = set_copy_str(env[*i], replace, &j);
    env[*i][j] = '\0';
    return (env);
}

char **set_can_i_replace(char *path, char **env, char *replace)
{
    int	i = 0;

    while (env[i] != NULL && my_strcmp_equal(replace, env[i]) != 1)
    i++;
    if (env[i] != NULL) {
        env = set_replace_this(env, replace, path, &i);
        return (env);
    } else {
        env = set_stock_env(env, 1, replace, path);
        return (env);
    }
    return (0);
}