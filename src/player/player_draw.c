/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:42:33 by efinda            #+#    #+#             */
/*   Updated: 2025/01/23 08:56:57 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	bresenham_circle(t_cub *cub, int cx, int cy, int radius)
{
	int	x;
	int	y;
	int	decision;

	x = -1;
	y = radius;
	decision = 3 - 2 * radius;
	while (++x <= y)
	{
		my_mlx_pixel_put(&cub->minimap.img, cx + x, cy + y, 0xFF0000);
		my_mlx_pixel_put(&cub->minimap.img, cx - x, cy + y, 0xFF0000);
		my_mlx_pixel_put(&cub->minimap.img, cx + x, cy - y, 0xFF0000);
		my_mlx_pixel_put(&cub->minimap.img, cx - x, cy - y, 0xFF0000);
		my_mlx_pixel_put(&cub->minimap.img, cx + y, cy + x, 0xFF0000);
		my_mlx_pixel_put(&cub->minimap.img, cx - y, cy + x, 0xFF0000);
		my_mlx_pixel_put(&cub->minimap.img, cx + y, cy - x, 0xFF0000);
		my_mlx_pixel_put(&cub->minimap.img, cx - y, cy - x, 0xFF0000);
		if (decision < 0)
			decision = decision + 4 * x + 6;
		else
		{
			decision = decision + 4 * (x - y) + 10;
			y--;
		}
	}
}

static void	init_vars(t_plane tmp, t_point *d, t_point *s, int *error)
{
	d->x = abs(tmp.x - tmp.x0);
	d->y = -abs(tmp.y - tmp.y0);
	if (tmp.x0 < tmp.x)
		s->x = 1;
	else
		s->x = -1;
	if (tmp.y0 < tmp.y)
		s->y = 1;
	else
		s->y = -1;
	*error = d->x + d->y;
}

static void	bresenham_line(t_cub *cub, t_plane tmp, t_point d, t_point s)
{
	int	error;
	int	e2;

	init_vars(tmp, &d, &s, &error);
	while (1)
	{
		my_mlx_pixel_put(&cub->minimap.img, tmp.x0, tmp.y0, 0xFF0000);
		if (tmp.x0 == tmp.x && tmp.y0 == tmp.y)
			break ;
		e2 = 2 * error;
		if (e2 >= d.y)
		{
			if (tmp.x0 == tmp.x)
				break ;
			error += d.y;
			tmp.x0 += s.x;
		}
		if (e2 <= d.x)
		{
			if (tmp.y0 == tmp.y)
				break ;
			error += d.x;
			tmp.y0 += s.y;
		}
	}
}

void	draw_player(t_cub *cub)
{
	int		radius;
	t_plane	tmp;

	radius = 5;
	while (--radius >= 0)
		bresenham_circle(cub, cub->player.pos.x0, cub->player.pos.y0, radius);
	cub->player.pos.x = cub->player.pos.x0 + ((cub->player.size.x * 2)
			* cos(cub->player.angle * (M_PI / 180.0)));
	cub->player.pos.y = cub->player.pos.y0 - ((cub->player.size.y * 2)
			* sin(cub->player.angle * (M_PI / 180.0)));
	tmp = cub->player.pos;
	bresenham_line(cub, tmp, (t_point){0, 0}, (t_point){0, 0});
}
