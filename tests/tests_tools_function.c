/*
** EPITECH PROJECT, 2020
** tests_tools_function
** File description:
** tests_tools_function
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "minishell.h"

Test(my_len_str, test_len_str, .timeout = 1)
{
    char *array = NULL;
    char *array_result = "st";

    array = my_len_str("str");
    cr_assert_str_eq(array, array_result);
}

Test(my_strcmpp, test_strcmpp_0, .timeout = 1)
{
    int return_val = 0;

    return_val = my_strcmpp("include", "include");
    cr_assert_eq(return_val, 0);
}

Test(my_strcmpp, test_strcmpp_1, .timeout = 1)
{
    int return_val = 0;

    return_val = my_strcmpp("include", "includ");
    cr_assert_eq(return_val, 1);
}

Test(my_strcmpp, test_strcmpp_2, .timeout = 1)
{
    int return_val = 0;

    return_val = my_strcmpp("includ", "include");
    cr_assert_eq(return_val, -1);
}

Test(my_putstr, test_my_putstr, .timeout = 1)
{
    int return_val = 0;

    return_val = my_putstr("include");
    cr_assert_eq(return_val, 0);
}