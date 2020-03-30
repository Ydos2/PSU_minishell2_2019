/*
** EPITECH PROJECT, 2020
** stock_env
** File description:
** stock_env
*/

#include "minishell.h"

char **set_norme_stock(char **env, char **copy_env)
{
    int i = 0;
    int j = 0;

    for (; env[i] != NULL; i++) {
        j = 0;
        for (; env[i][j] != '\0'; j++);
        copy_env[i] = malloc(sizeof(char) * (j + 1));
        for (j = 0; env[i][j] != '\0'; j++)
            copy_env[i][j] = env[i][j];
        copy_env[i][j] = '\0';
    }
    return (copy_env);
}

char **set_copy_line(char **copy_env, int i, char *str, char *path)
{
    int j = 0;
    int k = 0;

    for (; str != NULL && str[j] != '\0'; k++, j++)
        copy_env[i][k] = str[j];
    j = 0;
    copy_env[i][k] = '=';
    k++;
    for (; path != NULL && path[j] != '\0'; k++, j++)
        copy_env[i][k] = path[j];
    copy_env[i][k] = '\0';
    return (copy_env);
}

char **set_new_line(char *str, char **copy_env, char *path, int i)
{
    int j = 0;
    int k = 0;

    for (; str != NULL && str[j] != '\0'; j++);
    for (; path != NULL && path[k] != '\0'; k++);
    copy_env[i] = malloc(sizeof(char) * (j + k + 2));
    copy_env = set_copy_line(copy_env, i, str, path);
    j = 0;
    k = 0;
    return (copy_env);
}

char **set_stock_env(char **env, int size, char *str, char *path)
{
    char **copy_env;
    int i = 0;

    for (; env[i] != NULL; i++);
    copy_env = malloc(sizeof(char *) * (i + size + 1));
    copy_env[i + size] = NULL;
    copy_env = set_norme_stock(env, copy_env);
    if (str != NULL)
        copy_env = set_new_line(str, copy_env, path, i + size - 1);
    return (copy_env);
}