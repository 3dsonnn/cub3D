# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: efinda <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/09 09:28:49 by efinda            #+#    #+#              #
#    Updated: 2025/01/09 13:24:29 by efinda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#.SILENT:

NAME = cub3D

CC = cc
MLXPATH = minilibx-linux
FLAGS = -Wall -Wextra -Werror -I./$(MLXPATH) -O3
LIBS =	-L./$(MLXPATH) -lmlx -lX11 -lXext -lm
RM = rm -f

SRC = *.c
LIBFT =	libft/libft.a
MINILIBX = $(MLXPATH)/libmlx.a

OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(LIBFT) $(MINILIBX) $(OBJ_DIR) $(NAME)

$(LIBFT):
	@$(MAKE) -s -C libft

$(MINILIBX):
	@$(MAKE) -C $(MLXPATH)

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_DIR)/%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(LIBS) $(LIBFT) -o $@

clean:
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C $(MLXPATH) clean
	$(MAKE) -s -C libft clean

fclean: clean
	@$(RM) $(NAME)
	$(MAKE) -s -C libft fclean

re: fclean all
		$(MAKE) -s -C libft re

.PHONY: all clean fclean re