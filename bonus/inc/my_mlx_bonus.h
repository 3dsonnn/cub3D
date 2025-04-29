/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:52:08 by efinda            #+#    #+#             */
/*   Updated: 2025/04/27 11:50:50 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_MLX_BONUS_H
# define MY_MLX_BONUS_H

# include "../../libft/libft.h"
# include "cub3D_bonus.h"
# include "struct_bonus.h"

typedef struct s_img_to_img
{
	t_img	*dst;
	t_img	src;
	t_img	*aux;
	t_point	dst_point;
	t_point	src_point;
	t_point	size;
	int filter : 1;
	int		color_aux;
	int		color;
}			t_img_to_img;

extern void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
extern int	my_mlx_get_pixel(t_img img, int x, int y);
extern int	my_mlx_get_rgb_color(int r, int g, int b);
extern void	my_mlx_get_rgb_values(int color, int rgb[3]);
void		my_mlx_init_img(t_img *img);
void		my_mlx_destroy_img(void *mlx, t_img *img);
void		my_mlx_new_img(void *mlx, t_img *img, t_point size);
void		my_mlx_resize_img(void *mlx, t_img *img, t_point size);
void		my_mlx_get_data_addr(t_img *img);
int			my_mlx_get_transparent_color(int back, int fore, double level);
void		my_mlx_put_img_to_img(t_img_to_img base);

#endif