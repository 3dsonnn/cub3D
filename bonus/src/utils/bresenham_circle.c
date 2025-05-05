/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_circle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:06:49 by efinda            #+#    #+#             */
/*   Updated: 2025/05/04 13:04:54 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static void	bresenham_circle_paint_loop(t_img *img, t_point x_axis, int y,
		int color)
{
	int	i;

	i = x_axis.x;
	while (i <= x_axis.y)
	{
		my_mlx_pixel_put(img, i, y, color);
		i++;
	}
}

void	bresenham_circle_get_axis(t_plane *axis, t_point center, t_point limits,
		int flag)
{
	if (flag)
	{
		axis->x0 = center.x - limits.x;
		axis->y0 = center.y - limits.y;
		axis->x = center.x + limits.x;
		axis->y = center.y + limits.y;
	}
	else
	{
		axis->x0 = center.x - limits.y;
		axis->y0 = center.y - limits.x;
		axis->x = center.x + limits.y;
		axis->y = center.y + limits.x;
	}
}

void	bresenham_circle(t_bresenham_circle circle)
{
	while (++circle.limits.x <= circle.limits.y)
	{
		bresenham_circle_get_axis(&circle.axis, circle.center, circle.limits,
			1);
		bresenham_circle_paint_loop(circle.img, (t_point){circle.axis.x0,
			circle.axis.x}, circle.axis.y, circle.color);
		if (circle.axis.y0 != circle.axis.y)
			bresenham_circle_paint_loop(circle.img, (t_point){circle.axis.x0,
				circle.axis.x}, circle.axis.y0, circle.color);
		bresenham_circle_get_axis(&circle.axis, circle.center, circle.limits,
			0);
		bresenham_circle_paint_loop(circle.img, (t_point){circle.axis.x0,
			circle.axis.x}, circle.axis.y, circle.color);
		if (circle.axis.y0 != circle.axis.y)
			bresenham_circle_paint_loop(circle.img, (t_point){circle.axis.x0,
				circle.axis.x}, circle.axis.y0, circle.color);
		if (circle.decision < 0)
			circle.decision += 4 * circle.limits.x + 6;
		else
		{
			circle.decision += 4 * (circle.limits.x - circle.limits.y) + 10;
			circle.limits.y--;
		}
	}
}
