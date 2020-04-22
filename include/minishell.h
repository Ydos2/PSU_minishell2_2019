/*
** EPITECH PROJECT, 2020
** ls
** File description:
** ls
*/

#ifndef LS_H_
#define LS_H_
#include <stddef.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>

typedef struct mini
{
    int quit;
    int ret_nbr;
    int i;
    int j;
    int space;
    char **flag;
    char **flag_2;
    char **envp;
    char *cd_old;
    char *cd_new;
    int nbr_pipe;
    char *separator;
    char *separator_double;
} mini_t;

// main.c
void my_free_array(char **array);

// initialise.c
mini_t *initialise_var_start(mini_t *mini);
int set_exit(mini_t *mini, char *line);
int get_exit(char **flag, int nbr);
void draw_exit(mini_t *mini, char **flag, int nbr);

// minishell.c
int initialise_minishell(mini_t *mini, char **envp);
int initialise_shell(mini_t *mini);

// len_parameters.c
char **verif_pipe(mini_t *mini, char *line);

// command_execute.c
void set_other_command(mini_t *mini, char *line, char **envp, int space);
void set_command_not_find(char *line);

// tools_fonction.c
int my_strcmpp(char const *s1, char const *s2);
char *my_len_str(char *str);
int my_putstr(char const *str);
void my_putchar(char c);
int my_strcmp_equal(char *s1, char *s2);

// cd.c
int initialise_cd(char *line, char **envp, mini_t *mini);
char *get_path(char *line, mini_t *mini);
char *get_cd_solo(char **envp, mini_t *mini);
void set_file_directory(char *str);
void set_cd_less(mini_t *mini);

// unix_argument.c
int set_unix(mini_t *mini, char *line, char **envp);
char *get_unix_arg(mini_t *mini, char *line);

// env.c
char *set_path(char *line, char **envp, mini_t *mini);
int get_env_path(char **envp, mini_t *mini);
char *set_test_path(char **envp, char *line, int k, mini_t *mini);
int initialise_envv(char **envp, char *line);

// setenv.c
int initialise_setenvv(char *line, mini_t *mini);
char *set_copy_str(char *str, char *copy, int *j);
char **set_replace_this(char **env, char *path, char *replace, int *i);
char **set_can_i_replace(char *path, char **env, char *replace);

// unsetenv.c
int initialise_unsetenvv(char *line, char **envp, mini_t *mini);
char *set_copy_norm(char *env, char *copy_env);
char **set_copy_env_unset(char **env, char **copy_env, int i);
char **my_unset(char **env, int i);
char **can_i_remove(char **env, char *del);

// signal.c
void set_signal_Handler();

// my_str_to_word_array.c
char **my_str_to_word_array(char *str);
void my_free_and_set(char **array, int offset, char *to_free);
void my_attribute_line(char *buffer, char **array, int *k, int *array_nb);
int my_strlen_word(char *str, int *cursor);
int my_count_word(char *str);

// my_str_cat_malloc.c
int my_strlen_protect(char *str);
char *my_strcat_malloc(char *dest, char *src);

// my_memset.c
void my_memset(char *buffer, int size);

// clear_str.c
char *my_clear_begin(char *str);
char *my_clear_space(char *str);
char *my_clear_str(char *str);
int my_strlen(char const *str);

// stock_env.c
char **set_norme_stock(char **env, char **copy_env);
char **set_copy_line(char **copy_env, int i, char *str, char *path);
char **set_new_line(char *str, char **copy_env, char *path, int i);
char **set_stock_env(char **env, int size, char *str, char *path);

// execute.c
int set_ex(mini_t *mini, char *line, int space);
void initialise_ex(mini_t *mini, char *path);
int set_file_type(char *str);

// line_formatting.c
int set_line_formatting(char *line);

// my_strncmp.c
int my_strncmp(char *s1, char *s2, int n, int space);

// my_puterror.c
int my_puterror(char const *str);
void my_putchar_error(char c);

// my_malloc_array.c
char **my_malloc_array(int x, int y);

// dup.c
int get_dup_arguments(mini_t *mini, char *line, char *line_2);
char *parssing_path(char *line);

// double_right.c
int get_double_dup_arguments(mini_t *mini, char *line, char *line_2);

// pipe.c
int get_pipe_arguments(mini_t *mini, char *line, char *line_2);

// double_left
int get_left_arguments(mini_t *mini, char *line, char *line_2);

// error.c
void error_manager(int arg);

#endif /* !LS_H_ */