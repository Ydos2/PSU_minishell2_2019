/*
** EPITECH PROJECT, 2020
** my_str_to_word_array
** File description:
** my_str_to_word_array
*/

#include "minishell.h"

int my_count_word(char *str)
{
    int word = 0;
    int i = 0;
    int spaced = 0;

    while (str && str[i]) {
        if (str[i] != ' ' && spaced == 0) {
            word++;
            spaced = 1;
        }
        if (str[i] == ' ')
            spaced = 0;
        i++;
    }
    return (word);
}

int my_strlen_word(char *str, int *cursor)
{
    int i = 0;

    while (str && str[*cursor] != ' ') {
        *cursor = *cursor + 1;
        i++;
    }
    return (i);
}

void my_attribute_line(char *buffer, char **array, int *k, int *array_nb)
{
    buffer[*k] = '\0';
    array[*array_nb] = NULL;
    array[*array_nb] = my_strcat_malloc(array[*array_nb], buffer);
    my_memset(buffer, 100);
    *k = 0;
    *array_nb = *array_nb + 1;
}

void my_free_and_set(char **array, int offset, char *to_free)
{
    array[offset] = NULL;
    free(to_free);
}

char **my_str_to_word_array(char *str)
{
    char **array;
    int i = 0;
    int k = 0;
    int array_nb = 0;
    char buffer[1000];

    str =  my_clear_str(str);
    array = malloc(sizeof(char *) * (my_count_word(str) + 1));
    while (str && str[i]) {
        if (str[i] != ' ') {
            buffer[k] = str[i];
            k++;
            i++;
        } else
            i++;
        if ((str[i] == ' ' || str[i] == '\0') && buffer[0] != '\0')
            my_attribute_line(buffer, array, &k, &array_nb);
    }
    my_free_and_set(array, array_nb, str);
    return (array);
}