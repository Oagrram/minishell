# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aymhabib <aymhabib@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/16 02:00:08 by aymhabib          #+#    #+#              #
#    Updated: 2020/12/28 15:40:10 by oagrram          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= minishell

SRC= main.c ft_cd.c

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
