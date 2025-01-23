# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: efinda <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/09 09:28:49 by efinda            #+#    #+#              #
#    Updated: 2025/01/23 13:34:48 by efinda           ###   ########.fr        #
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
		src/error.c 								\
		src/checks/map.c 							\
		src/checks/checks.c 						\
		src/checks/elements.c 						\
		src/checks/map_utils.c 						\
		src/checks/elements_utils.c 				\
		src/t_row/t_row.c 							\
		src/t_row/t_row_aux.c 						\
		src/my_mlx/my_mlx_init.c 					\
		src/my_mlx/my_mlx_hook.c 					\
		src/my_mlx/my_mlx_utils.c 					\
		src/cub3D/cub3D.c 							\
		src/free.c 									\
		src/minimap/minimap.c 						\
		src/minimap/minimap_init.c 					\
		src/minimap/minimap_init_tiles.c			\
		src/minimap/minimap_link_tiles.c			\
		src/minimap/cast_rays.c						\
		src/minimap/cast_rays_utils.c				\
		src/player/player.c 						\
		src/player/players_movements_0.c 			\
		src/player/players_movements_1.c 			\
		src/player/players_movements_2.c 			\
		src/player/players_rotation.c				\
		src/player/player_draw.c					\
		src/player/player_fov.c						\

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