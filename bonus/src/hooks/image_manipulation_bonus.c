/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_manipulation_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:34:02 by efinda            #+#    #+#             */
/*   Updated: 2025/04/27 12:24:47 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

void	my_mlx_draw_horizontal_lines_to_img(t_img *img, t_point crd,
		t_point size, int color)
{
	t_point	iter;

	iter = (t_point){.x = -1, .y = -1};
	if (!img || crd.x < 0 || crd.x > img->width || crd.y < 0
		|| crd.y > img->height || size.x <= 0 || size.y <= 0)
		return ;
	if (crd.x + size.x > img->width)
		size.x = img->width - crd.x;
	if (crd.y + size.y > img->height)
		size.y = img->height - crd.y;
	while (++iter.y < size.y)
	{
		iter.x = -1;
		while (++iter.x < size.x)
			my_mlx_pixel_put(img, crd.x + iter.x, crd.y + iter.y, color);
	}
}
