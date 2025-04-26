/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:27:58 by efinda            #+#    #+#             */
/*   Updated: 2025/04/26 21:15:23 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../../libft/libft.h"
# include "mlx.h"
# include "my_mlx_bonus.h"
# include "struct_bonus.h"
# include <X11/Xlib.h>
# include <errno.h>
# include <fcntl.h>
# include <float.h>
# include <math.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define FONT "-sony-fixed-medium-r-normal--24-240-75-75-c-120-iso8859-1"

# define WIDTH 1920
# define HEIGHT 1010
# define HALF_WIDTH 960
# define HALF_HEIGHT 505
# define GUN_WIDTH 640
# define GUN_HEIGHT 640
# define HEALTH_BAR_WIDTH 300
# define HEALTH_BAR_HEIGHT 30

# define TILE 64
# define MINI_TILE 20
# define ROT 0.05
# define SPEED 5.0
# define FOV 2.094395102393195
# define PLAYER_RADIUS 10

# define DIGITS "0123456789"

# define SPACE 32
# define ALT 65513
# define CTRL 65507
# define ESC 65307
# define AKEY 97
# define DKEY 100
# define SKEY 115
# define WKEY 119
# define EKEY 101
# define LEFT 65361
# define RIGHT 65363
# define UP 65362
# define DOWN 65364

# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define DARK_GRAY 0x333333
# define TRANSPARENT 0xFF000000

//  CHECKS
extern char			*get_element_name(char c);
void				check_fc(t_scene *scene);
void				check_fc_syntax(t_scene *scene, char *info, char *id);
void				divide_to_conquer(t_scene *scene, char *id, int rgb[3],
						int i);
void				check_texture(t_scene *scene);
void				check_element(t_scene *scene);
void				skip_empty_lines(t_scene *scene);
void				extend_map(t_map *map, t_row **head, t_row *tmp);
void				fulfill_map(t_scene *scene, t_map *map, t_row *head);
void				fill_map(t_scene *scene, t_map *map, int diff);
void				check_doors(t_scene *scene, t_door door, t_row *head,
						t_row *tail);
void				checks(t_cub *cub, int ac, char **av);
void				is_surrounded(t_scene *scene, t_map *map, t_row *head,
						t_row *tile);
void				check_duplicate_id(t_scene *scene, char ID);
char				*get_explicit_error_message(t_scene *scene, t_strs strs);
void				check_starting_position(t_scene *scene, t_map *map,
						t_row *head, t_iter iter);

// MINIMAP
void				minimap(t_cub *cub);
void				set_tiles(t_cub *cub, int i, int j);
void				link_tiles(t_cub *cub, int i, int j);
void				init_minimap(t_cub *cub);
void				update_obx(t_cub *cub, t_tile *corners[4], t_tile **tiles);
void				miniplayer(t_cub *cub, t_point tile_min);

//  MY_MLX
void				my_mlx_hook(t_cub *cub);
extern void			alt_space(t_cub *cub, int keycode);
void				init_mlx(t_cub *cub);
void				my_mlx_put_img_to_img(t_img *dst, t_img src, t_point crd,
						int flag);
void				my_mlx_draw_horizontal_lines_to_img(t_img *img, t_point crd,
						t_point size, int color);

//  PLAYER
void				init_player(t_cub *cub);
int					move_player(t_cub *cub, int keycode);
int					rotate_player(t_cub *cub, int keycode);
void				player(t_cub *cub);
extern bool			is_door(t_tile *tile);
void				open_or_close_door(t_tile *cur);

// SPRITES
void				get_sprites_images(t_cub *cub, int i);
void				put_gun_frame(t_cub *cub, t_img frame);

//  RAYS
void				init_rays(t_cub *cub);
void				get_rays(t_cub *cub, int i);
void				check_horizontal_intersection(t_cub *cub, t_ray *ray,
						int check_wall);
void				check_vertical_intersection(t_cub *cub, t_ray *ray,
						int check_wall);
int					is_wall(t_cub *cub, double x, double y);
int					inside_map(t_cub *cub, double x, double y);
extern int			face_down(double angle);
extern int			face_right(double angle);
void				get_texture(t_cub *cub, t_ray *ray, double angle,
						t_point dir);

//  CUB3D
void				init_dfl(t_cub *cub);
void				cub3D(t_cub *cub);

//  UTILS
double				ft_normalizer(double angle);
int					ft_map(int old_value, int old_limits[2], int new_limits[2]);
void				exit_error(char *message, t_scene *scene);
void				my_mlx_error_free(t_cub *cub, char *message);
void				bresenham_circle(t_bresenham_circle circle);
void				bresenham_line(t_bresenham_line line);
void				free_tiles(t_tile ***tiles, int i, int size);
void				destroy_all_imgs(t_cub *cub);
unsigned long long	get_current_time(void);
char				*join_strs(t_strs strs);
void				map_crd_error_message(t_scene *scene, char *message, char c,
						t_nbr aux);

//  T_ROW
void				free_row(t_row **head, t_row *ref);
void				add_row_back(t_row **head, t_row *new);
void				add_row_front(t_row **head, t_row *new);
t_row				*new_row(char *str, int nbr);
t_row				*get_last_row(t_row *head);
char				**row_to_mtx(t_row *head);
void				free_rows(t_row **head);
void				trim_rows(t_row **head);
t_point				rows_size(t_row *head);

//  T_MAP_CRD
char				*map_crds_to_str(t_map_crd *head, char *base);
void				add_map_crd(t_map_crd **head, t_map_crd *new);
t_map_crd			*new_map_crd(char c, char *col, char *line);
void				free_map_crds(t_map_crd **head);

#endif
