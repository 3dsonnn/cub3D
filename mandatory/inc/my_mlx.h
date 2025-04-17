/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:52:08 by efinda            #+#    #+#             */
/*   Updated: 2025/04/17 01:05:58 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_MLX_H
# define MY_MLX_H

# include "../../libft/libft.h"
# include "cub3D.h"
# include "struct.h"

extern void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
extern int	my_mlx_get_pixel(t_img img, int x, int y);
extern int	my_mlx_get_rgb_color(int r, int g, int b);
extern void	my_mlx_get_rgb_values(int color, int rgb[3]);
void		my_mlx_init_img(t_img *img);
void		my_mlx_destroy_img(void *mlx, t_img *img);
void		my_mlx_new_img(void *mlx, t_img *img, t_point size);
void		my_mlx_resize_img(void *mlx, t_img *img, t_point size);
void		my_mlx_get_data_addr(t_img *img);

#endif