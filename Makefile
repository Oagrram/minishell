# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aymhabib <aymhabib@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/16 02:00:08 by aymhabib          #+#    #+#              #
#    Updated: 2021/02/05 16:46:36 by oagrram          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= minishell

SRC= src/minishell.c \
		src/tools.c \
		src/expansions.c \
		src/exec_cmd.c \
		src/data_to_list.c \
		src/builtins.c \
		src/builtins/ft_cd.c \
		src/builtins/ft_echo.c \
		src/builtins/ft_env.c \
		src/builtins/ft_setenv.c \
		src/builtins/ft_unsetenv.c \

OBJ= $(SRC:.c=.o)

CC= gcc
CFLAGS= -Wall -Wextra -Werror

.PHONY: all
all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	$(CC) -g $(CFLAGS) libft/libft.a $(OBJ) -o $(NAME)
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
		make clean -C libft
		rm -f $(OBJ)

.PHONY: fclean
fclean: clean
		make fclean -C libft
		rm -f $(NAME)

re: fclean all
