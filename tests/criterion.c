/*
** EPITECH PROJECT, 2019
** criterion
** File description:
** criterion
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "minishell.h"

Test(initialise_var_start, test_structure_1, .timeout = 1)
{
    mini_t *mini = NULL;

    mini = initialise_var_start(mini);
    cr_assert_eq(mini->quit, 0);
}

Test(set_file_type, test_permission, .timeout = 1)
{
    int return_val = 0;

    return_val = set_file_type("include");
    cr_assert_eq(return_val, 1);
}