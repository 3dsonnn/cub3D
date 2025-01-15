/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 22:53:50 by efinda            #+#    #+#             */
/*   Updated: 2025/01/15 11:07:17 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

inline int	mlx_get_rgb_color(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	my_mlx_pixel_put(t_img *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_len) + x * (image->bpp / 8);
	*(unsigned int *)(dst) = color;
}
