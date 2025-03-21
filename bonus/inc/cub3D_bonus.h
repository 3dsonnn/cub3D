/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:27:58 by efinda            #+#    #+#             */
/*   Updated: 2025/03/21 23:58:31 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../../libft/libft.h"
# include "mlx.h"
# include "struct_bonus.h"
# include <errno.h>
# include <fcntl.h>
# include <float.h>
# include <math.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define FONT "-sony-fixed-medium-r-normal--24-240-75-75-c-120-iso8859-1"

# define TILE 64
# define ROT 0.05
# define SPEED 5.0
# define FOV 2.094395102393195
# define PLAYER_RADIUS 10

# define SPACE 32
# define ALT 65513
# define CTRL 65507
# define ESC 65307
# define AKEY 97
# define DKEY 100
# define SKEY 115
# define WKEY 119
# define LEFT 65361
# define RIGHT 65363

# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define TRANSPARENT 0xFF000000

//  CHECKS
char				*get_element_str(char c);
void				check_fc(t_scene *scene);
void				check_texture(t_scene *scene);
void				check_element(t_scene *scene);
char				*skip_empty_lines(t_scene *scene);
void				fill_map(t_scene *scene, t_map *map);
void				checks(t_cub *cub, int ac, char **av);
void				fulfill_map(t_scene *scene, t_map *map);
void				is_surrounded(t_scene *scene, t_map *map, t_point iter);
void				check_duplicate_id(t_scene *scene, char ID);
void				check_map_start(t_scene *scene, t_map *map);
void				trimap(char ***map, int begin, int end, t_iter iter);
char				*get_explicit_error_message(t_scene *scene, t_strs strs);
void				check_starting_position(t_scene *scene, t_map *map, int i,
						int j);

// MINIMAP
void				minimap(t_cub *cub);
void				set_tiles(t_cub *cub, int i, int j);
void				link_tiles(t_cub *cub, int i, int j);
void				init_minimap(t_cub *cub, int i, int j);
void				paint_obx(t_cub *cub, t_tile *topleft, t_point *minip);
void				paint_minimap_tile(t_cub *cub, int i, int j, int color);
void				update_obx(t_cub *cub);
void				miniplayer(t_cub *cub, t_point base, t_point tile_min);

//  MY_MLX
void				my_mlx_hook(t_cub *cub);
extern void			alt(t_cub *cub);
extern void			space(t_cub *cub);
void				init_mlx(t_cub *cub, int i);
extern int			my_mlx_get_rgb_color(int r, int g, int b);
extern void			my_mlx_get_rgb_values(int color, int rgb[3]);
int					my_mlx_get_transparent_color(int back, int fore,
						double level);
void				my_mlx_free(t_cub *cub, char *message, t_plane flag);
extern void			my_mlx_pixel_put(t_img *image, int x, int y, int color);
extern int			my_mlx_get_pixel(t_img image, int x, int y);
void				my_mlx_put_img_to_img(t_img *dst, t_img src, int x, int y);

//  PLAYER
void				init_player(t_cub *cub);
void				rotate_player(t_cub *cub, double angle_delta);
void				move_player(t_cub *cub, double forward, double strafe,
						t_dpoint new_pos);

//  RAYS
extern void			init_rays(t_cub *cub);
void				get_rays(t_cub *cub, int i);
void				check_horizontal_intersection(t_cub *cub, int i);
void				check_vertical_intersection(t_cub *cub, int i);
int					is_wall(t_cub *cub, double x, double y);
int					inside_map(t_cub *cub, double x, double y);
extern int			face_down(double angle);
extern int			face_right(double angle);
extern t_texture	*get_texture(t_cub *cub, double angle, t_point dir);

//  CUB3D
void				cub3D(t_cub *cub);

// PAINTING
void				paint(t_cub *cub, int i, int j, t_point pixel);

//  UTILS
double				ft_normalizer(double angle);
int					ft_map(int old_value, int old_limits[2], int new_limits[2]);
void				exit_error(char *message, t_scene *scene);
void				bresenham_circle(t_bresenham_circle circle);
void				bresenham_line(t_bresenham_line line);
void				free_tiles(t_tile ***tiles, int i, int size);

//  T_ROW
t_rows				*new_row(char *str);
int					rowlen(t_rows *head);
void				free_rows(t_rows **head);
char				**row_to_mtx(t_rows *head);
void				add_row(t_rows **head, t_rows *_new);

#endif
