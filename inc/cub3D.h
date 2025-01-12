/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:27:58 by efinda            #+#    #+#             */
/*   Updated: 2025/01/12 16:35:40 by efinda           ###   ########.fr       */
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

# define ESC 65307
# define LEFT 65362
# define RIGHT 65364
# define AKEY 65
# define DKEY 68
# define SKEY 83
# define WKEY 87

//  CHECKS
void	checks(t_scene *scene, int ac, char **av);
void	check_element(t_scene *scene);
void	fill_texture(t_scene *scene, char ID, int fd);
void	fill_fc(t_scene *scene, char ID, int *rgb, int i);
//  MAP
void	escape_empty_lines(t_scene *scene);
void	fill_map(t_scene *scene, t_map *map);
void	is_surrounded(t_scene *scene, t_map *map, int p[3]);
void	check_starting_position(t_scene *scene, t_map *map);
bool	my_flood_fill(t_map *map);

//  ERRORS
void	exit_error(char *message, t_scene *scene);

//  T_ROW
void	add_row(t_rows **head, t_rows *new);
int		rowlen(t_rows *head);
char	**row_to_mtx(t_rows *head);
void	free_rows(t_rows **head);
t_rows	*new_row(char *str);

#endif