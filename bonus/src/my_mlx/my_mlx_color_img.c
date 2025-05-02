/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_color_img.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:40:17 by efinda            #+#    #+#             */
/*   Updated: 2025/04/30 18:08:08 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/my_mlx_bonus.h"

void	my_mlx_color_img(t_img *img, int color)
{
	t_point	iter;

	if (!img || !img->addr || img->height <= 0 || img->width <= 0)
		return ;
	iter = (t_point){-1, -1};
	while (++iter.y < img->height)
	{
		iter.x = -1;
		while (++iter.x < img->width)
			my_mlx_pixel_put(img, iter.x, iter.y, color);
	}
}
