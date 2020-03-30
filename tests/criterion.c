/*
** EPITECH PROJECT, 2019
** criterion
** File description:
** criterion
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "minishell.h"

Test(set_line_formatting, line_formatting_0, .timeout = 1)
{
    int return_value = 0;

    return_value = set_line_formatting("cd");
    cr_assert_eq(return_value, 0);
}

Test(set_line_formatting, line_formatting_1, .timeout = 1)
{
    int return_value = 0;

    return_value = set_line_formatting("    \tcd");
    cr_assert_eq(return_value, 4);
}


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

Test(initialise_var_start, test_structure_1, .timeout = 1)
{
    mini_t *mini = NULL;

    mini = initialise_var_start(mini);
    cr_assert_eq(mini->quit, 0);
}