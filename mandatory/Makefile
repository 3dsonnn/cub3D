# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: efinda <efinda@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/09 09:28:49 by efinda            #+#    #+#              #
#    Updated: 2025/02/18 22:26:45 by efinda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

NAME = cub3D
#	-Wall -Wextra -Werror
CC = cc
MLXPATH = minilibx-linux
FLAGS = -I./$(MLXPATH) -O3
LIBS =	-L./$(MLXPATH) -lmlx -lX11 -lXext -lm
RM = rm -rf

SRC =	src/main.c 									\
		src/checks/map.c 							\
		src/checks/checks.c 						\
		src/checks/elements.c 						\
		src/checks/textures.c						\
		src/checks/map_utils.c 						\
		src/checks/explicit_errors.c 				\
		src/checks/ceiling_and_floor.c				\
		src/my_mlx/init.c 							\
		src/my_mlx/hooks.c 							\
		src/my_mlx/utils.c 							\
		src/cub3D/cub3D.c 							\
		src/player/aux.c 							\
		src/player/init.c 							\
		src/player/move.c 							\
		src/player/rotation.c						\
		src/raycast/get_rays.c						\
		src/raycast/vertical.c						\
		src/raycast/horizontal.c					\
		src/t_row/t_row.c 							\
		src/t_row/t_row_aux.c 						\
		src/utils/error.c 							\
		src/utils/ft_math.c							\
		src/utils/bresenham.c						\

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
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) $(LIBS) -o $@

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
