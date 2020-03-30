/*
** EPITECH PROJECT, 2020
** unsetenv
** File description:
** unsetenv
*/

#include "minishell.h"

int initialise_unsetenvv(char *line, char **envp, mini_t *mini)
{
    char **array = NULL;

    array = my_str_to_word_array(line);
    if (array[1] != NULL) {
        envp = can_i_remove(envp, array[1]);
        mini->envp = envp;
    } else
        write(1, "unsetenv: Too few arguments.\n", 29);
    return (1);
}

char *set_copy_norm(char *env, char *copy_env)
{
    int i = 0;

    for (; env[i] != '\0'; i++)
        copy_env[i] = env[i];
    copy_env[i] = '\0';
    return (copy_env);
}

char **set_copy_env_unset(char **env, char **copy_env, int i)
{
    int j = 0;
    int k = 0;

    for (int nbr = 0; env[nbr] != NULL; nbr++) {
        if (nbr != i) {
            for (k = 0; env[nbr][k] != '\0'; k++);
            copy_env[j] = malloc(sizeof(char) * (k + 1));
            copy_env[j] = set_copy_norm(env[nbr], copy_env[j]);
            j++;
        }
    }
    return (copy_env);
}

char **my_unset(char **env, int i)
{
    int j = 0;
    char **copy_env = NULL;

    for (; env[j] != NULL; j++);
    copy_env = malloc(sizeof(char *) * j);
    copy_env[j - 1] = NULL;
    copy_env = set_copy_env_unset(env, copy_env, i);
    return (copy_env);
}

char **can_i_remove(char **env, char *del)
{
    int i = 0;

    while (env[i] != NULL && my_strcmp_equal(del, env[i]) != 1)
    i++;
    env = my_unset(env, i);
    return (env);
}