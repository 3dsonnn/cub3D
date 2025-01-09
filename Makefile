# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: efinda <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/09 09:28:49 by efinda            #+#    #+#              #
#    Updated: 2025/01/09 11:53:31 by efinda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = CC
FLAGS = -Wall -Wextra -Werror -I./$(MLXPATH) -O3
MLXPATH = minilibx-linux
LIBS =	-L./$(MLXPATH) -lmlx -lX11 -lXext -lm
RM = rm -f

SRC = *.c
MINILIBX = $(MLXPATH)/libmlx.a

OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(MINILIBX) $(OBJ_DIR) $(NAME)

$(MINILIBX):
	@$(MAKE) -C $(MLXPATH)

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_DIR)/%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(LIBS) -o $@

clean:
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C $(MLXPATH) clean

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re