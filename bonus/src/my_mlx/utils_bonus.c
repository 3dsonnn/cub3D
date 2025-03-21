/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 22:53:50 by efinda            #+#    #+#             */
/*   Updated: 2025/03/21 23:04:01 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

int	my_mlx_get_transparent_color(int back, int fore, double level)
{
	int	rgb[3];
	int	back_rgb[3];
	int	fore_rgb[3];

	my_mlx_get_rgb_values(back, back_rgb);
	my_mlx_get_rgb_values(fore, fore_rgb);
	rgb[0] = (int)((fore_rgb[0] * level) + (back_rgb[0] * (1 - level)));
	rgb[1] = (int)((fore_rgb[1] * level) + (back_rgb[1] * (1 - level)));
	rgb[2] = (int)((fore_rgb[2] * level) + (back_rgb[2] * (1 - level)));
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

inline int	my_mlx_get_rgb_color(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

inline void	my_mlx_get_rgb_values(int color, int rgb[3])
{
	rgb[0] = (color >> 16) & 0xFF;
	rgb[1] = (color >> 8) & 0xFF;
	rgb[2] = color & 0xFF;
}

inline void	my_mlx_pixel_put(t_img *image, int x, int y, int color)
{
	if (x < 0 || x >= image->width || y < 0 || y >= image->height)
		return ;
	*(image->addr + y * image->line_len + x) = color;
}

inline int	my_mlx_get_pixel(t_img *image, int x, int y)
{
	if (!image || x < 0 || x >= image->width || y < 0 || y >= image->height)
		return (BLACK);
	return (*(image->addr + y * image->line_len + x));
}
