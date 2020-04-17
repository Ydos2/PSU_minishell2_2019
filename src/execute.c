/*
** EPITECH PROJECT, 2020
** execute
** File description:
** execute
*/

#include "minishell.h"

int set_ex(mini_t *mini, char *line, int space)
{
    char *path = NULL;
    int nbr = 0;

    for (int i = space; line[i] != '\0'; i++, nbr++)
        if (line[i] == ' ')
            break;
    path = malloc(sizeof(char) * nbr);
    for (int i = 0, j = space; nbr != 0; i++, j++, nbr--)
        path[i] = line[j];
    mini->flag = my_str_to_word_array(line);
    if (set_file_type(path) == 0)
        initialise_ex(mini, path);
    return (1);
}

void initialise_ex(mini_t *mini, char *path)
{
    pid_t pid = 0;
    int arg = 0;

    pid = fork();
    if (pid == 0)
        execve(path, mini->flag, mini->envp);
    else if (pid > 0)
        waitpid(pid, &arg, 0);
    error_manager(arg);
    kill(pid, SIGKILL);
}

int set_file_type(char *str)
{
    struct stat sb;

    if (stat(str, &sb) != -1) {
        if (S_ISREG(sb.st_mode) != 0) {
            return (0);
        } else {
            my_puterror(str);
            write(2, ": Permission denied.\n", 21);
            return (1);
        }
    }
    return (0);
}