/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 22:53:50 by efinda            #+#    #+#             */
/*   Updated: 2025/02/05 23:29:49 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/obx.h"

inline int	my_mlx_get_rgb_color(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	my_mlx_clear_image(t_img *image)
{
	int	x;
	int	y;

	y = -1;
	while (++y < image->height)
	{
		x = -1;
		while (++x < image->width)
			my_mlx_pixel_put(image, x, y, BLACK);
	}
}

void	my_mlx_pixel_put(t_img *image, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= image->width || y < 0 || y >= image->height)
		return ;
	dst = image->addr + (y * image->line_len) + x * (image->bpp / 8);
	*(unsigned int *)(dst) = color;
}
