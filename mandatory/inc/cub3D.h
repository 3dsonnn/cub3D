/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:27:58 by efinda            #+#    #+#             */
/*   Updated: 2025/03/04 13:29:55 by efinda           ###   ########.fr       */
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
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define TILE 64

# define DEG_TO_RAD(angle) ((angle) * (M_PI / 180.0))
# define FOV DEG_TO_RAD(120)
# define SPEED 3.0

# define FACE_DOWN(angle) ((angle) > 0 && (angle) < M_PI)
# define FACE_UP(angle) (!(FACE_DOWN(angle)))
# define FACE_RIGHT(angle) ((angle) < M_PI_2 || (angle) > (3 * M_PI_2))
# define FACE_LEFT(angle) (!(FACE_RIGHT(angle)))

# define ESC 65307
# define AKEY 97
# define DKEY 100
# define SKEY 115
# define WKEY 119
# define LEFT 65361
# define RIGHT 65363

//  CHECKS
char		*get_element_str(char c);
void		check_fc(t_scene *scene);
void		check_texture(t_scene *scene);
void		check_element(t_scene *scene);
char		*skip_empty_lines(t_scene *scene);
void		fill_map(t_scene *scene, t_map *map);
void		checks(t_cub *cub, int ac, char **av);
void		fulfill_map(t_scene *scene, t_map *map);
void		is_surrounded(t_scene *scene, t_map *map);
void		check_duplicate_id(t_scene *scene, char ID);
void		check_map_start(t_scene *scene, t_map *map);
void		trimap(char ***map, int begin, int end, t_iter iter);
char		*get_explicit_error_message(t_scene *scene, t_strs strs);
void		check_starting_position(t_scene *scene, t_map *map, int i, int j);

//  MY_MLX
void		my_mlx_hook(t_cub *cub);
void		init_mlx(t_cub *cub, int i);
extern int	my_mlx_get_rgb_color(int r, int g, int b);
void		my_mlx_free(t_cub *cub, char *message, t_plane flag);
extern void	my_mlx_pixel_put(t_img *image, int x, int y, int color);

//  PLAYER
void		init_player(t_cub *cub);
void		rotate_player(t_cub *cub, int flag);
void		move_player(t_cub *cub, t_dpoint new_pos, t_plane flag);

//  RAYS
extern void	init_rays(t_cub *cub);
void		get_rays(t_cub *cub, int i);
void		check_horizontal_intersection(t_cub *cub, int i);
void		check_vertical_intersection(t_cub *cub, int i);
int			is_wall(t_cub *cub, double x, double y);
int			inside_map(t_cub *cub, double x, double y);

//  CUB3D
void		cub3D(t_cub *cub);

// PAINTING
void		paint(t_cub *cub, int i);

//  UTILS
double		ft_normalizer(double angle);
void		exit_error(char *message, t_scene *scene);
void		bresenham_circle(t_cub *cub, int cx, int cy, int radius);
void		bresenham_line(t_cub *cub, t_plane crd, t_point dist, t_point dir);

//  T_ROW
t_rows		*new_row(char *str);
int			rowlen(t_rows *head);
void		free_rows(t_rows **head);
char		**row_to_mtx(t_rows *head);
void		add_row(t_rows **head, t_rows *_new);

#endif
