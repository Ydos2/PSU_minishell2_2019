/*
** EPITECH PROJECT, 2020
** cd
** File description:
** cd
*/

#include "minishell.h"

int initialise_cd(char *line, char **envp, mini_t *mini)
{
    int a = 0;
    char *path = NULL;
    char **array = my_str_to_word_array(line);

    if (array[1] == NULL)
        path = get_cd_solo(envp, mini);
    else if (my_strncmp(array[1], "-", 1, 0) == 0) {
        set_cd_less(mini);
        return (1);
    } else
        path = get_path(line, mini);
    a = chdir(path);
    if (a == -1)
        set_file_directory(path);
    return (1);
}

char *get_path(char *line, mini_t *mini)
{
    char **array = my_str_to_word_array(line);

    mini->cd_old = malloc(sizeof(char) * my_strlen(mini->cd_new));
    for (int i = 0; mini->cd_new[i] != '\0'; i++)
        mini->cd_old[i] = mini->cd_new[i];
    mini->cd_new = malloc(sizeof(char) * my_strlen(array[1]));
    for (int i = 0; array[1][i] != '\0'; i++)
        mini->cd_new[i] = array[1][i];
    return (array[1]);
}

char *get_cd_solo(char **envp, mini_t *mini)
{
    char *path = NULL;
    int i = 0, j = 0, k = 0;

    for (i = 0; envp[i] != NULL; i++) {
        if (envp[i][0] == 'H' && envp[i][1] == 'O' &&
        envp[i][2] == 'M' && envp[i][3] == 'E' &&
        envp[i][4] == '=')
            break;
    }
    for (j = 0; envp[i][j] != '\0'; j++);
    path = malloc(sizeof(char) * j);
    for (j = 0, k = 5; envp[i][k] != '\0'; j++, k++)
        path[j] = envp[i][k];
    mini->cd_old = malloc(sizeof(char) * my_strlen(mini->cd_new));
    for (int i = 0; mini->cd_new[i] != '\0'; i++)
        mini->cd_old[i] = mini->cd_new[i];
    mini->cd_new = malloc(sizeof(char) * my_strlen(path));
    for (int i = 0; path[i] != '\0'; i++)
        mini->cd_new[i] = path[i];
    return (path);
}

void set_file_directory(char *str)
{
    struct stat sb;

    if (stat(str, &sb) != -1) {
        if (S_ISDIR(sb.st_mode) == 0) {
            my_putstr(str);
            write(1, ": Not a directory.\n", 19);
        }
    } else {
        my_putstr(str);
        write(1, ": No such file or directory.\n", 29);
    }
}

void set_cd_less(mini_t *mini)
{
    char *port = NULL;

    if (mini->cd_old == NULL) {
        write(1, ": No such file or directory.\n", 29);
    } else {
        chdir(mini->cd_old);
        port = malloc(sizeof(char) * my_strlen(mini->cd_new));
        for (int i = 0; mini->cd_new[i] != '\0'; i++)
            port[i] = mini->cd_new[i];
        mini->cd_new = malloc(sizeof(char) * my_strlen(mini->cd_old));
        for (int i = 0; mini->cd_old[i] != '\0'; i++)
            mini->cd_new[i] = mini->cd_old[i];
        mini->cd_old = malloc(sizeof(char) * my_strlen(port));
        for (int i = 0; port[i] != '\0'; i++)
            mini->cd_old[i] = port[i];
    }
}