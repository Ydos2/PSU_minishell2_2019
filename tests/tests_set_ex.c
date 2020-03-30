/*
** EPITECH PROJECT, 2020
** tests_set_ex
** File description:
** tests_set_ex
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "minishell.h"

Test(set_file_type, set_exect_0_type, .timeout = 1)
{
    int return_value = 0;

    return_value = set_file_type("mysh");
    cr_assert_eq(return_value, 0);
}

Test(set_file_type, set_exect_1_type, .timeout = 1)
{
    int return_value = 0;

    return_value = set_file_type("include");
    cr_assert_eq(return_value, 1);
}