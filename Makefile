# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: efinda <efinda@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/09 09:28:49 by efinda            #+#    #+#              #
#    Updated: 2025/04/01 18:18:56 by efinda           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

NAME = cub3D
NAME_BONUS = cub3D_bonus

CC = cc
FLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRC =	mandatory/src/main.c 									\
		mandatory/src/checks/map.c 								\
		mandatory/src/checks/checks.c 							\
		mandatory/src/checks/elements.c 						\
		mandatory/src/checks/textures.c							\
		mandatory/src/checks/is_surrounded.c 					\
		mandatory/src/checks/utils.c 							\
		mandatory/src/checks/ceiling_and_floor.c				\
		mandatory/src/my_mlx/init.c 							\
		mandatory/src/my_mlx/hooks.c 							\
		mandatory/src/my_mlx/utils.c 							\
		mandatory/src/cub3D/cub3D.c 							\
		mandatory/src/cub3D/painting.c 							\
		mandatory/src/player/init.c 							\
		mandatory/src/player/move.c 							\
		mandatory/src/raycast/aux.c								\
		mandatory/src/raycast/init_rays.c						\
		mandatory/src/raycast/vertical.c						\
		mandatory/src/raycast/horizontal.c						\
		mandatory/src/t_row/t_row.c 							\
		mandatory/src/t_row/t_row_aux.c 						\
		mandatory/src/utils/error.c 							\
		mandatory/src/utils/ft_math.c							\

SRC_BONUS =	bonus/src/main_bonus.c 									\
			bonus/src/init/init_bonus.c								\
			bonus/src/init/mlx_init_bonus.c							\
			bonus/src/checks/map_bonus.c 							\
			bonus/src/checks/checks_bonus.c 						\
			bonus/src/checks/elements_bonus.c 						\
			bonus/src/checks/textures_bonus.c						\
			bonus/src/checks/is_surrounded_bonus.c 					\
			bonus/src/checks/utils_bonus.c 							\
			bonus/src/checks/ceiling_and_floor_bonus.c				\
			bonus/src/hooks/hooks_bonus.c 							\
			bonus/src/hooks/hooks_aux_bonus.c 						\
			bonus/src/hooks/image_manipulation_bonus.c 				\
			bonus/src/cub3D/cub3D_bonus.c 							\
			bonus/src/cub3D/painting_bonus.c 						\
			bonus/src/player/init_bonus.c 							\
			bonus/src/player/move_bonus.c 							\
			bonus/src/player/rotate_bonus.c							\
			bonus/src/raycast/aux_bonus.c							\
			bonus/src/raycast/get_rays_bonus.c						\
			bonus/src/raycast/vertical_bonus.c						\
			bonus/src/raycast/horizontal_bonus.c					\
			bonus/src/t_row/t_row_bonus.c 							\
			bonus/src/t_row/t_row_aux_bonus.c 						\
			bonus/src/utils/bresenham_bonus.c						\
			bonus/src/utils/free_bonus.c 							\
			bonus/src/utils/error_bonus.c 							\
			bonus/src/utils/ft_math_bonus.c							\
			bonus/src/minimap/init_bonus.c							\
			bonus/src/minimap/linkage_bonus.c						\
			bonus/src/minimap/settings_bonus.c						\
			bonus/src/minimap/obx_bonus.c							\
			bonus/src/minimap/paint_bonus.c							\
			bonus/src/minimap/minimap_bonus.c						\
			bonus/src/minimap/miniplayer_bonus.c					\
			bonus/src/sprites/init_bonus.c							\
			bonus/src/sprites/sprites_bonus.c						\
			bonus/src/my_mlx/my_mlx_init_img_bonus.c				\
			bonus/src/my_mlx/my_mlx_pixel_put_bonus.c				\
			bonus/src/my_mlx/my_mlx_get_pixel_bonus.c				\
			bonus/src/my_mlx/my_mlx_new_img_bonus.c					\
			bonus/src/my_mlx/my_mlx_destroy_img_bonus.c				\
			bonus/src/my_mlx/my_mlx_resize_img_bonus.c				\
			bonus/src/my_mlx/my_mlx_get_rgb_color_bonus.c			\
			bonus/src/my_mlx/my_mlx_get_rgb_values_bonus.c			\
			bonus/src/my_mlx/my_mlx_get_data_addr_bonus.c			\
			bonus/src/my_mlx/my_mlx_get_transparent_color_bonus.c	\

LIBFTPATH = libft
LIBFT =	$(LIBFTPATH)/libft.a

MLXPATH = minilibx-linux
MLX = $(MLXPATH)/libmlx.a
FLAGS = -I./$(MLXPATH) -O3
LIBS =	-L./$(MLXPATH) -lmlx -lX11 -lXext -lm

OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

OBJ_DIR_BONUS = obj_bonus
OBJ_BONUS = $(SRC_BONUS:%.c=$(OBJ_DIR_BONUS)/%.o)

all: $(LIBFT) $(MLX) $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) $(LIBS) -o $@

bonus: $(LIBFT) $(MLX) $(OBJ_DIR_BONUS) $(NAME_BONUS)

$(OBJ_DIR_BONUS):
	@mkdir -p $@

$(OBJ_DIR_BONUS)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME_BONUS): $(OBJ_BONUS)
	$(CC) $(FLAGS) $(OBJ_BONUS) $(LIBFT) $(LIBS) -o $@

$(LIBFT):
	@$(MAKE) -s -C $(LIBFTPATH)

$(MLX):
	@$(MAKE) -C $(MLXPATH)

clean:
	@$(RM) $(OBJ_DIR) $(OBJ_DIR_BONUS)
	@$(MAKE) -C $(MLXPATH) clean
	@$(MAKE) -s -C $(LIBFTPATH) clean

fclean: clean
	@$(RM) $(NAME) $(NAME_BONUS)
	$(MAKE) -s -C $(LIBFTPATH) fclean

re: fclean all
		$(MAKE) -s -C $(LIBFTPATH) re

rebonus: fclean bonus
		$(MAKE) -s -C $(LIBFTPATH) re

.PHONY: all clean fclean re bonus
