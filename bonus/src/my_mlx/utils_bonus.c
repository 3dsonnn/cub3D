/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 22:53:50 by efinda            #+#    #+#             */
/*   Updated: 2025/03/04 17:30:56 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

inline int	my_mlx_get_rgb_color(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

inline	void	my_mlx_pixel_put(t_img *image, int x, int y, int color)
{
	if (x < 0 || x >= image->width || y < 0 || y >= image->height)
		return ;
	*(image->addr + y * image->line_len + x) = color;
}
