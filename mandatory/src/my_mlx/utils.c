/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 22:53:50 by efinda            #+#    #+#             */
/*   Updated: 2025/03/21 23:11:51 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

inline int	my_mlx_get_rgb_color(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

inline void	my_mlx_pixel_put(t_img *image, int x, int y, int color)
{
	if (!image || x < 0 || x >= image->width || y < 0 || y >= image->height)
		return ;
	*(image->addr + y * image->line_len + x) = color;
}

inline int	my_mlx_get_pixel(t_img image, int x, int y)
{
	if (x < 0 || x >= image.width || y < 0 || y >= image.height)
		return (BLACK);
	return (*(image.addr + y * image.line_len + x));
}
