/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_fov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:20:49 by efinda            #+#    #+#             */
/*   Updated: 2025/01/23 08:56:46 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

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

void	draw_fov(t_cub *cub)
{
	t_plane	start_fov;
    t_plane	end_fov;

	start_fov = cub->player.pos;
    end_fov = cub->player.pos;
	start_fov.x = start_fov.x0 + ((cub->player.size.x * 2)
			* cos(cub->player.fov.x * (M_PI / 180.0)));
	start_fov.y = start_fov.y0 - ((cub->player.size.y * 2)
			* sin(cub->player.fov.x * (M_PI / 180.0)));
    end_fov.x = end_fov.x0 + ((cub->player.size.x * 2)
			* cos(cub->player.fov.y * (M_PI / 180.0)));
	end_fov.y = end_fov.y0 - ((cub->player.size.y * 2)
			* sin(cub->player.fov.y * (M_PI / 180.0)));
	bresenham_line(cub, start_fov, (t_point){0, 0}, (t_point){0, 0});
    bresenham_line(cub, end_fov, (t_point){0, 0}, (t_point){0, 0});
}
