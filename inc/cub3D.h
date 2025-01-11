/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:27:58 by efinda            #+#    #+#             */
/*   Updated: 2025/01/11 11:15:03 by efinda           ###   ########.fr       */
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

# define ESC 65307
# define LEFT 65362
# define RIGHT 65364
# define A_KEY 65
# define D_KEY 68
# define S_KEY 83
# define W_KEY 87

//  CHECKS
void	checks(t_scene *scene, int ac, char **av);
void	check_element(t_scene *scene);
void	fill_texture(t_scene *scene, char ID, int fd);
void	fill_fc(t_scene *scene, char ID, int *rgb, int i);

#endif