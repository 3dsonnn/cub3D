/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_drawn_triangle.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:54:53 by efinda            #+#    #+#             */
/*   Updated: 2025/04/30 18:13:46 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/my_mlx_bonus.h"

void	my_mlx_drawn_triangle(t_img *img, t_point crd, int size, int color)
{
	int		half_base;
	int		height;
	int		row_width;
	t_point	iter;

	if (!img || !img->addr || crd.x <= 0 || crd.y <= 0 || size <= 0)
		return ;
	height = size;
	half_base = size / 2;
	iter = (t_point){-1, -1};
	while (++iter.y < height)
	{
		row_width = (int)((double)iter.y / height * half_base);
		iter.x = -row_width;
		while (iter.x <= row_width)
		{
			my_mlx_pixel_put(img, crd.x + iter.x, crd.y + iter.y, color);
			iter.x++;
		}
	}
}
