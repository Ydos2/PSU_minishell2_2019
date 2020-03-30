/*
** EPITECH PROJECT, 2020
** tests_tools_function_next
** File description:
** tests_tools_function_next
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "minishell.h"

Test(my_strcmp_equal, test_strcmpp_equal_0, .timeout = 1)
{
    int return_val = 0;

    return_val = my_strcmp_equal("include", "include");
    cr_assert_eq(return_val, 0);
}