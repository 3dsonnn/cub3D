/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:27:58 by efinda            #+#    #+#             */
/*   Updated: 2025/01/23 15:32:36 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "mlx.h"
# include "struct.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define FOV 180.0

# define WIDTH 1920
# define HEIGHT 1080

# define MINIWIDTH 1728
# define MINIHEIGHT 972

# define ESC 65307

# define AKEY 97
# define DKEY 100
# define SKEY 115
# define WKEY 119

# define NUMLEFT 65430
# define NUMRIGHT 65432
# define NUMUP 65431
# define NUMUPLEFT 65429
# define NUMUPRIGHT 65434
# define NUMDOWN 65433
# define NUMDOWNLEFT 65436
# define NUMDOWNRIGHT 65435

# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363

//  DELETE IT LATER

//  CHECKS
void		checks(t_cub *cub, int ac, char **av);
//      ELEMENTS
void		check_element(t_scene *scene);
void		fill_texture(t_scene *scene, char ID, char *path);
void		fill_fc(t_scene *scene, char ID, int *rgb, int i);
//      MAP
void		escape_empty_lines(t_scene *scene);
void		fill_map(t_scene *scene, t_map *map);
void		is_surrounded(t_scene *scene, t_map *map);
void		check_starting_position(t_scene *scene, t_map *map);

//  ERRORS
void		exit_error(char *message, t_scene *scene);

//  T_ROW
void		add_row(t_rows **head, t_rows *_new);
int			rowlen(t_rows *head);
char		**row_to_mtx(t_rows *head);
void		free_rows(t_rows **head);
t_rows		*new_row(char *str);

//  MY_MLX
void		my_mlx_init(t_cub *cub);

//  MY_MLX_HOOK
void		my_mlx_hook(t_cub *cub);

//  MY_MLX_UTILS
void		my_mlx_pixel_put(t_img *image, int x, int y, int color);
extern int	my_mlx_get_rgb_color(int r, int g, int b);

//  PLAYER
void		init_player(t_cub *cub, int i, int j);
void		move_player(t_cub *cub, t_plane flag);
void		rotate_player(t_cub *cub, int flag);
int			check_players_newpos_overlap(t_cub *cub, t_plane flag);
int			check_player_left(t_cub *cub, t_plane new_pos, int i);
int			check_player_right(t_cub *cub, t_plane new_pos, int i);
int			check_player_down(t_cub *cub, t_plane new_pos, int i);
int			check_player_up(t_cub *cub, t_plane new_pos, int i);
void		draw_player(t_cub *cub);
void		draw_fov(t_cub *cub);
int			check_if_same_tile(t_plane tile, int tilex0, int x, int y);

//  CUB3D
void		cub3D(t_cub *cub);
void		display(t_cub *cub);

//  MINIMAP
void		minimap(t_cub *cub, int i, int j);
void		init_minimap(t_cub *cub, int i, int j);
void		link_tiles(t_cub *cub, int i, int j);
void		init_tiles(t_cub *cub, int i, int j);
void		set_tiles_colors(t_cub *cub, int i, int j);
void		cast_rays(t_cub *cub, int i);
void		draw_ray(t_cub *cub, t_ray ray);

//  FREE
void		all_free(t_cub *cub, int i);

#endif