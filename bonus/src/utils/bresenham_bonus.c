/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:28:25 by efinda            #+#    #+#             */
/*   Updated: 2025/03/13 02:21:13 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static void	init_line(t_bresenham_line *line)
{
	line->dist.x = abs(line->crd.x - line->crd.x0);
	line->dist.y = -abs(line->crd.y - line->crd.y0);
	if (line->crd.x0 < line->crd.x)
		line->dir.x = 1;
	else
		line->dir.x = -1;
	if (line->crd.y0 < line->crd.y)
		line->dir.y = 1;
	else
		line->dir.y = -1;
	line->error = line->dist.x + line->dist.y;
}

void	bresenham_line(t_bresenham_line line)
{
	init_line(&line);
	while (1)
	{
		my_mlx_pixel_put(line.img, line.crd.x0, line.crd.y0, GREEN);
		if (line.crd.x0 == line.crd.x && line.crd.y0 == line.crd.y)
			break ;
		line.updated_error = 2 * line.error;
		if (line.updated_error >= line.dist.y)
		{
			line.error += line.dist.y;
			line.crd.x0 += line.dir.x;
		}
		if (line.updated_error <= line.dist.x)
		{
			line.error += line.dist.x;
			line.crd.y0 += line.dir.y;
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
