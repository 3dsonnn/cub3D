/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:27:58 by efinda            #+#    #+#             */
/*   Updated: 2025/04/17 02:22:50 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../../libft/libft.h"
# include "mlx.h"
# include "struct.h"
# include "my_mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <float.h>
# include <math.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define TILE 64
# define ROT 0.05
# define SPEED 5.0
# define FOV 2.094395102393195
# define PLAYER_RADIUS 10

# define ESC 65307
# define AKEY 97
# define DKEY 100
# define SKEY 115
# define WKEY 119
# define LEFT 65361
# define RIGHT 65363

# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define TRANSPARENT 0xFF000000

//  CHECKS
char				*get_element_str(char c);
void				check_fc(t_scene *scene);
void				check_texture(t_scene *scene);
void				check_element(t_scene *scene, int *flag);
void				skip_empty_lines(t_scene *scene);
void				fulfill_map(t_scene *scene, t_map *map);
void				fill_map(t_scene *scene, t_map *map);
void				checks(t_cub *cub, int ac, char **av);
void				is_surrounded(t_scene *scene, t_map *map, t_point iter);
void				check_duplicate_id(t_scene *scene, char ID);
void				check_map_start(t_scene *scene, t_map *map);
char				*get_explicit_error_message(t_scene *scene, t_strs strs);
void				check_starting_position(t_scene *scene, t_map *map, int i,
						int j);

//  MY_MLX
void				my_mlx_hook(t_cub *cub);
void				init_mlx(t_cub *cub, int i);
void				my_mlx_free(t_cub *cub, char *message, t_plane flag);

//  PLAYER
void				init_player(t_cub *cub);
void				rotate_player(t_cub *cub, double angle_delta);
void				move_player(t_cub *cub, double forward, double strafe,
						t_dpoint new_pos);

//  RAYS
extern void			init_rays(t_cub *cub);
void				check_horizontal_intersection(t_cub *cub, int i);
void				check_vertical_intersection(t_cub *cub, int i);
int					is_wall(t_cub *cub, double x, double y);
int					inside_map(t_cub *cub, double x, double y);
extern int			face_down(double angle);
extern int			face_right(double angle);
extern t_texture	*get_texture(t_cub *cub, double angle, t_point dir);

//  CUB3D
void				cub3d(t_cub *cub, int j);

// PAINTING
void				paint(t_cub *cub, int i, int j, t_point pixel);

//  UTILS
double				ft_normalizer(double angle);
int					ft_map(int old_value, int old_limits[2], int new_limits[2]);
void				exit_error(char *message, t_scene *scene);

//  T_ROW
t_rows				*new_row(char *str);
int					rowlen(t_rows *head);
void				free_rows(t_rows **head);
char				**row_to_mtx(t_rows *head);
void				add_row(t_rows **head, t_rows *_new);

#endif
