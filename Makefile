# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgarcia <jgarcia@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/10 16:44:37 by jgarcia           #+#    #+#              #
#    Updated: 2022/07/10 16:44:40 by jgarcia          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asteroid
CURRENT_DIR = $(shell pwd)
CC = gcc
CFLAGS = -Wall -Wextra -g -c

INC = -Iminilibx-linux/
LINK = -Lminilibx-linux -lmlx_Linux -lXext -lX11 -lm -lz

SRC = main.c init.c graph_utils.c render.c tests.c

OBJ = $(SRC:.c=.o)

RM = rm -f

all : $(NAME)

$(NAME): $(OBJ) $(CURRENT_DIR)/minilibx/libmlx_Linux.a
	$(CC) $(OBJ) $(LINK) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) $< -o $@

$(CURRENT_DIR)/minilibx/libmlx_Linux.a:
	make -C minilibx-linux

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: clean fclean all re