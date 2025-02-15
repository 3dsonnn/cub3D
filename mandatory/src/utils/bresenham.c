/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:28:25 by efinda            #+#    #+#             */
/*   Updated: 2025/02/10 14:26:09 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	init_line(t_plane crd, t_point *dist, t_point *dir, int *error)
{
	dist->x = abs(crd.x - crd.x0);
	dist->y = -abs(crd.y - crd.y0);
	if (crd.x0 < crd.x)
		dir->x = 1;
	else
		dir->x = -1;
	if (crd.y0 < crd.y)
		dir->y = 1;
	else
		dir->y = -1;
	*error = dist->x + dist->y;
}

void	bresenham_line(t_cub *cub, t_plane crd, t_point dist, t_point dir)
{
	int	error;
	int	updated_error;

	init_line(crd, &dist, &dir, &error);
	while (1)
	{
		my_mlx_pixel_put(&cub->img, crd.x0, crd.y0, 0xFF0000);
		if (crd.x0 == crd.x && crd.y0 == crd.y)
			break ;
		updated_error = 2 * error;
		if (updated_error >= dist.y)
		{
			if (crd.x0 == crd.x)
				break ;
			error += dist.y;
			crd.x0 += dir.x;
		}
		if (updated_error <= dist.x)
		{
			if (crd.y0 == crd.y)
				break ;
			error += dist.x;
			crd.y0 += dir.y;
		}
	}
}

void	bresenham_circle(t_cub *cub, int cx, int cy, int radius)
{
	int	x;
	int	y;
	int	decision;

	x = -1;
	y = radius;
	decision = 3 - 2 * radius;
	while (++x <= y)
	{
		my_mlx_pixel_put(&cub->img, cx + x, cy + y, 0xFF0000);
		my_mlx_pixel_put(&cub->img, cx - x, cy + y, 0xFF0000);
		my_mlx_pixel_put(&cub->img, cx + x, cy - y, 0xFF0000);
		my_mlx_pixel_put(&cub->img, cx - x, cy - y, 0xFF0000);
		my_mlx_pixel_put(&cub->img, cx + y, cy + x, 0xFF0000);
		my_mlx_pixel_put(&cub->img, cx - y, cy + x, 0xFF0000);
		my_mlx_pixel_put(&cub->img, cx + y, cy - x, 0xFF0000);
		my_mlx_pixel_put(&cub->img, cx - y, cy - x, 0xFF0000);
		if (decision < 0)
			decision = decision + 4 * x + 6;
		else
		{
			decision = decision + 4 * (x - y) + 10;
			y--;
		}
	}
}
