/*
** EPITECH PROJECT, 2020
** tests_str_to_word_array_1
** File description:
** tests_str_to_word_array_1
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "minishell.h"

Test(my_str_to_word_array, test_global_my_str_to_word_array, .timeout = 1)
{
    char **array = NULL;
    char *array_result[] = {
        "ls",
        "-l",
        "-a",
    };

    array = my_str_to_word_array("  ls   -l  -a  ");
    for (int i = 0; i != 3; i++)
        cr_assert_str_eq(array[i], array_result[i]);
}