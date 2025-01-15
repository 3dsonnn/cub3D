/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:27:58 by efinda            #+#    #+#             */
/*   Updated: 2025/01/15 02:21:31 by efinda           ###   ########.fr       */
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

# define WIDTH 1920
# define HEIGHT 1020
# define ESC 65307
# define LEFT 65362
# define RIGHT 65364
# define AKEY 65
# define DKEY 68
# define SKEY 83
# define WKEY 87

//  DELETE IT LATER
void		print_map(t_map *map);

//  CHECKS
void		checks(t_scene *scene, int ac, char **av);
void		check_element(t_scene *scene);
void		fill_texture(t_scene *scene, char ID, char *path);
void		fill_fc(t_scene *scene, char ID, int *rgb, int i);
//  MAP
void		escape_empty_lines(t_scene *scene);
void		fill_map(t_scene *scene, t_map *map);
void		is_surrounded(t_scene *scene, t_map *map);
void		check_starting_position(t_scene *scene, t_map *map);
void		my_flood_fill(t_map *map, int x, int y);

//  ERRORS
void		exit_error(char *message, t_scene *scene);

//  T_ROW
void		add_row(t_rows **head, t_rows *new);
int			rowlen(t_rows *head);
char		**row_to_mtx(t_rows *head);
void		free_rows(t_rows **head);
t_rows		*new_row(char *str);

//  MY_MLX
void		my_mlx_init(t_cub *cub);
//  MY_MLX_HOOK
void	my_mlx_hook(t_cub *cub);
//  MY_MLX_UTILS
void		my_mlx_pixel_put(t_img *image, int x, int y, int color);
extern int	mlx_get_rgb_color(int r, int g, int b);

#endif