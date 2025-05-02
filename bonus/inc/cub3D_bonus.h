/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:27:58 by efinda            #+#    #+#             */
/*   Updated: 2025/05/02 04:35:18 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../../libft/libft.h"
# include "macros_bonus.h"
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
# include <time.h>
# include <unistd.h>

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
void				fill_map(t_scene *scene, t_map *map);
void				update_player(t_map *map, t_row *head);
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
void				paint_minimap(t_cub *cub, t_tile *topleft);
void				get_circle_img(t_img *dst, t_img src, t_point iter);
void				rotate_img(t_img *dst, t_img src, t_img *aux, double angle);
void				blit_rotated_img(t_img *dst, t_img src, t_point offset);

//  MY_MLX
void				my_mlx_hook(t_cub *cub);
extern void			alt_space(t_cub *cub, int keycode);
void				init_mlx(t_cub *cub);
int					my_mlx_mouse_click(int keycode, int x, int y, t_cub *cub);

//  PLAYER
void				init_player(t_cub *cub);
int					move_player(t_cub *cub, int keycode);
int					rotate_player(t_cub *cub, int keycode);
extern bool			is_door(t_tile *tile);
void				open_or_close_door(t_tile *cur);

// SPRITES
void				get_sprites_images(t_cub *cub, int i);
void				update_shooting_animation(t_img *back, t_sprite *sprites,
						unsigned long long cur_time);
void				put_shooting_animation(t_img *back, t_img frame,
						t_img clear);
void				get_clear_and_crosshair_imgs(t_cub *cub, t_img imgs[25]);

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

// PAINTING
void				paint_wall(t_cub *cub, t_ray *ray, t_point iter,
						t_point pixel);
void				paint_ceiling_and_floor(t_cub *cub, t_point iter);

//  CUB3D
void				init_dfl(t_cub *cub);
void				cub3d(t_cub *cub);

//  UTILS
double				ft_normalizer(double angle);
float				ft_clamp(float value, float min, float max);
int					ft_map(int old_value, int old_limits[2], int new_limits[2]);
void				exit_error(char *message, t_scene *scene);
void				my_mlx_error_free(t_cub *cub, char *message);
void				free_tiles(t_tile ***tiles, int i, int size);
void				destroy_all_imgs(t_cub *cub);
unsigned long long	get_current_time(void);
char				*join_strs(t_strs strs);
void				map_crd_error_message(t_scene *scene, char *message, char c,
						t_nbr aux);

//  T_ROW
void				add_row_back(t_row **head, t_row *new);
void				add_row_front(t_row **head, t_row *new);
t_row				*new_row(char *str, int nbr);
t_row				*get_last_row(t_row *head);
char				**row_to_mtx(t_row *head);
void				free_rows(t_row **head);
t_point				rows_size(t_row *head);
void				free_row(t_row **row);
void				trim_rows_vertically(t_row **head);
t_point				get_horizontal_limits(t_row *head);
void				trim_rows_horizontally(t_row **head, t_point limits);

//  T_MAP_CRD
char				*map_crds_to_str(t_map_crd *head, char *base);
void				add_map_crd(t_map_crd **head, t_map_crd *new);
t_map_crd			*new_map_crd(char c, char *col, char *line);
void				free_map_crds(t_map_crd **head);

#endif
