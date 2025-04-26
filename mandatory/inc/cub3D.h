/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:27:58 by efinda            #+#    #+#             */
/*   Updated: 2025/04/26 16:42:21 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../../libft/libft.h"
# include "mlx.h"
# include "my_mlx.h"
# include "struct.h"
# include <errno.h>
# include <fcntl.h>
# include <float.h>
# include <math.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WIDTH 1920
# define HEIGHT 1010
# define TILE 64
# define ROT 0.05
# define SPEED 5.0
# define FOV 2.094395102393195
# define PLAYER_RADIUS 10
# define DIGITS "0123456789"

# define ESC 65307
# define AKEY 97
# define DKEY 100
# define SKEY 115
# define WKEY 119
# define LEFT 65361
# define RIGHT 65363

# define TRANSPARENT 0xFF000000

//  CHECKS
void		init_dfl(t_cub *cub, int i);
extern char	*get_element_name(char c);
void		check_fc(t_scene *scene);
void		check_fc_syntax(t_scene *scene, char *info, char *id);
void		divide_to_conquer(t_scene *scene, char *id, int rgb[3], int i);
void		check_texture(t_scene *scene);
void		check_element(t_scene *scene);
void		skip_empty_lines(t_scene *scene);
void		fulfill_map(t_scene *scene, t_map *map, t_row *head);
void		fill_map(t_scene *scene, t_map *map);
void		checks(t_cub *cub, int ac, char **av);
void		is_surrounded(t_scene *scene, t_map *map, t_row *head, t_row *tile);
void		check_duplicate_id(t_scene *scene, char ID);
char		*get_explicit_error_message(t_scene *scene, t_strs strs);
void		check_starting_position(t_scene *scene, t_map *map, t_row *head,
				t_iter iter);

//  MY_MLX
void		my_mlx_hook(t_cub *cub);
void		init_mlx(t_cub *cub, int i);
void		my_mlx_free(t_cub *cub, char *message, t_plane flag);

//  PLAYER
void		init_player(t_cub *cub);
void		rotate_player(t_cub *cub, double angle_delta);
void		move_player(t_cub *cub, double forward, double strafe,
				t_dpoint new_pos);

//  RAYCAST
void		raycast(t_cub *cub, int j);
void		init_rays(t_cub *cub);
void		check_horizontal_intersection(t_cub *cub, t_ray *ray);
void		check_vertical_intersection(t_cub *cub, t_ray *ray);
int			is_wall(t_cub *cub, double x, double y);
extern int	inside_map(t_cub *cub, double x, double y);
extern int	face_down(double angle);
extern int	face_right(double angle);
void		get_texture(t_cub *cub, t_ray *ray, double angle, t_point dir);

//  UTILS
double		ft_normalizer(double angle);
int			ft_map(int old_value, int old_limits[2], int new_limits[2]);
void		exit_error(char *message, t_scene *scene);
char		*join_strs(t_strs strs);

//  T_ROW
void		free_row(t_row **head, t_row *ref);
void		add_row(t_row **head, t_row *new);
t_row		*new_row(char *str, int nbr);
t_row		*get_last_row(t_row *head);
char		**row_to_mtx(t_row *head);
void		free_rows(t_row **head);
void		trim_rows(t_row **head);
t_point		rows_size(t_row *head);

//  T_MAP_CRD
char		*map_crds_to_str(t_map_crd *head, char *base);
void		add_map_crd(t_map_crd **head, t_map_crd *new);
t_map_crd	*new_map_crd(char c, char *col, char *line);
void		free_map_crds(t_map_crd **head);

#endif
