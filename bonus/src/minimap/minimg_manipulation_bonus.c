/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimg_manipulation_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:21:47 by efinda            #+#    #+#             */
/*   Updated: 2025/05/04 13:29:56 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

void	get_circle_img(t_img *dst, t_img src, t_point iter)
{
	t_point	delta;
	t_point	center;
	t_point	pixel;

	center = (t_point){src.width / 2, src.height / 2};
	while (++iter.y < dst->height)
	{
		iter.x = -1;
		while (++iter.x < dst->width)
		{
			delta.x = iter.x - (MINI_TILE * 5);
			delta.y = iter.y - (MINI_TILE * 5);
			if (delta.x * delta.x + delta.y * delta.y <= (MINI_TILE * 5)
				* (MINI_TILE * 5))
			{
				pixel.x = center.x + delta.x;
				pixel.y = center.y + delta.y;
				my_mlx_pixel_put(dst, iter.x, iter.y, my_mlx_get_pixel(src,
						pixel.x, pixel.y));
			}
			else
				my_mlx_pixel_put(dst, iter.x, iter.y, TRANSPARENT);
		}
	}
}

static void	center_image(t_img *dst, t_img src, t_point *aux)
{
	t_point	offset;
	t_point	iter;

	iter = (t_point){-1, -1};
	offset.x = (dst->width - src.width) / 2;
	offset.y = (dst->height - src.height) / 2;
	while (++iter.y < src.height)
	{
		iter.x = -1;
		while (++iter.x < src.width)
			my_mlx_pixel_put(dst, iter.x + offset.x, iter.y + offset.y,
				my_mlx_get_pixel(src, iter.x, iter.y));
	}
	*aux = (t_point){-1, -1};
}

void	rotate_img(t_img *dst, t_img src, t_img *aux, double angle)
{
	t_dplane	tmp;
	t_dpoint	trig;
	t_point		center;
	t_point		iter;
	t_point		nearest;

	center_image(aux, src, &iter);
	center = (t_point){dst->width / 2, dst->height / 2};
	trig = (t_dpoint){cos(angle), sin(angle)};
	while (++iter.y < dst->height)
	{
		iter.x = -1;
		while (++iter.x < dst->width)
		{
			tmp.x0 = iter.x - center.x;
			tmp.y0 = iter.y - center.y;
			tmp.x = tmp.x0 * trig.x + tmp.y0 * trig.y;
			tmp.y = -tmp.x0 * trig.y + tmp.y0 * trig.x;
			tmp.x += center.x;
			tmp.y += center.y;
			nearest = (t_point){(int)(tmp.x + 0.5f), (int)(tmp.y + 0.5f)};
			my_mlx_pixel_put(dst, iter.x, iter.y, my_mlx_get_pixel(*aux,
					nearest.x, nearest.y));
		}
	}
}

void	blit_rotated_img(t_img *dst, t_img src, t_point offset)
{
	t_point	iter;
	int		color;

	iter = (t_point){-1, -1};
	while (++iter.y < src.height)
	{
		iter.x = -1;
		while (++iter.x < src.width)
		{
			color = my_mlx_get_pixel(src, iter.x, iter.y);
			if (color == BLACK || color == (int)TRANSPARENT)
				continue ;
			my_mlx_pixel_put(dst, iter.x + offset.x, iter.y + offset.y, color);
		}
	}
}
