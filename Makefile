##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

CC        =    gcc

SRC     =	src/initialise.c				\
			src/minishell.c					\
			src/tools_function.c			\
			src/cd.c						\
			src/unix_argument.c				\
			src/env.c						\
			src/unsetenv.c					\
			src/setenv.c					\
			src/signal.c					\
			src/my_str_to_word_array.c		\
			src/my_str_cat_malloc.c			\
			src/my_memset.c					\
			src/clear_str.c					\
			src/stock_env.c					\
			src/execute.c					\
			src/line_formatting.c			\
			src/my_strncmp.c				\
			src/my_puterror.c				\
			src/command_execute.c			\
			src/len_parameters.c			\
			src/my_malloc_array.c			\
			src/dup.c						\
			src/pipe.c						\
			src/double_right.c				\
			src/double_left.c				\
			src/error.c						\

OBJ     =	$(SRC:.c=.o) 			\

COVERAGE		=	$(SRC:.c=.gcda)				\
					$(MAIN_SRC:.c=.gcda)		\
					$(TEST_SRC:.c=.gcda)		\
					$(SRC:.c=.gcno)				\
					$(MAIN_SRC:.c=.gcno)		\
					$(TEST_SRC:.c=.gcno)		\

MAIN_SRC    =    src/main.c			\

MAIN_OBJ    =    $(MAIN_SRC:.c=.o)	\

CFLAGS    =    -I./include -Wextra -W -Wall -pedantic

TARGET    =		mysh		\

TEST_SRC     =		tests/criterion.c						\
					tests/tests_line_formatting.c			\
					tests/tests_set_ex.c					\
					tests/tests_str_to_word_array_1.c		\
					tests/tests_tools_function.c			\
					tests/tests_tools_function_next.c		\

TEST_OBJ     =     $(TEST_SRC:.c=.o)

TEST_TARGET     =     unit_tests

TEST_LFLAGS	=	-lcriterion

all: $(TARGET) ## Build the project

$(TARGET): build

build: $(OBJ) $(MAIN_OBJ) ## Compile the project
	@printf "\e[1;3;5;32m▀▄▀▄▀▄ Finished compiling sources ▄▀▄▀▄▀\e[0m\n"
	@$(CC) $(CFLAGS) $(OBJ) $(MAIN_OBJ) -o $(TARGET)
	@printf "[\e[1;34m-Link Obj-\e[0m] % 43s\n" $(OBJ) | tr ' ' '.'
	@printf "[\e[1;34m-Link Main-\e[0m] % 43s\n" $(MAIN_OBJ) | tr ' ' '.'
	@printf "\e[1;3;5;32m▀▄▀▄▀▄ Link all object ▄▀▄▀▄▀\e[0m\n"

%.o : %.c
	@$(CC) $(LFLAGS) $(CFLAGS) -c $< -o $@
	@printf "[\e[1;34m-Compiled-\e[0m] % 41s\n" $@ | tr ' ' '.'

clean: ## Clean the useless file
	@rm -f $(OBJ) $(MAIN_OBJ) $(TEST_OBJ) $(COVERAGE)

fclean: clean ## Clean the project
	@rm -f $(TARGET) $(TEST_TARGET)
	@printf "[\e[1;31m-RM-\e[0m] % 42s\n" $(TARGET) | tr ' ' '.'
	@printf "[\e[1;31m-RM-\e[0m] % 42s\n" $(TEST_TARGET) | tr ' ' '.'
	@printf "\e[1;3;5;32m▀▄▀▄▀▄ Finished RM ▄▀▄▀▄▀\e[0m\n"

re:    fclean all ## Clean then compile

tests_run: CFLAGS += --coverage ## Launch tests
tests_run: $(OBJ) $(TEST_OBJ)
	@printf "\e[1;32mFinished compiling sources\e[0m\n"
	@$(CC) $(CFLAGS) $(OBJ) $(TEST_OBJ) -o $(TEST_TARGET) $(TEST_LFLAGS)
	@printf "\e[1;3;5;32m▀▄▀▄▀▄ Tests the code ▄▀▄▀▄▀\e[0m\n"
	@./$(TEST_TARGET)
	@gcovr --exclude tests/
	@gcovr -b

re_tests: fclean tests_run ## Clean then tests

valgrind:	CFLAGS += -g3
valgrind: fclean all ## Launch valgrind
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

help: ## Help for the Makefile
	@cat $(MAKEFILE_LIST) | sed -En 's/^([a-zA-Z_-]+)\s*:.*##\s?(.*)/\1 "\2"/p' | xargs printf "\033[32m%-30s\033[0m %s\n"

.PHONY:	all build clean fclean re tests_run re_tests valgrind help