/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:35:12 by efinda            #+#    #+#             */
/*   Updated: 2025/01/23 15:07:10 by efinda           ###   ########.fr       */
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

void	draw_ray(t_cub *cub, t_ray ray)
{
    t_plane	line;

    line = cub->player.pos;
    if (ray.dhor < ray.dvert)
    {
        line.x = ray.hor.x;
        line.y = ray.hor.y;
    }
    else
    {
        line.x = ray.vert.x;
        line.y = ray.vert.y;
    }
    bresenham_line(cub, line, (t_point){0, 0}, (t_point){0, 0});
}
