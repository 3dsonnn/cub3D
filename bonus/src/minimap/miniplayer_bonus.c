/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniplayer_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 07:48:53 by efinda            #+#    #+#             */
/*   Updated: 2025/03/13 09:40:58 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static inline int	map(int old_value, int old_limits[2], int new_limits[2])
{
	double	ratio;
	double	old_range;
	double	new_range;

	old_range = old_limits[1] - old_limits[0];
	new_range = new_limits[1] - new_limits[0];
	ratio = (double)(old_value - old_limits[0]) / old_range;
	return ((int)(new_limits[0] + ratio * new_range));
}

static inline void	init_circle(t_bresenham_circle *circle, int cx, int cy,
		int radius)
{
	circle->color = RED;
	circle->center.x = cx;
	circle->center.y = cy;
	circle->radius = radius;
	circle->crd.x = -1;
	circle->crd.y = radius;
	circle->decision = 3 - 2 * radius;
}

void	miniplayer(t_cub *cub, t_point base, t_point tile_min)
{
	t_bresenham_line	line;
	t_bresenham_circle	circle;

	line.img = &cub->img;
	circle.img = &cub->img;
	line.color = GREEN;
	line.crd.x0 = map((int)cub->player.pos.x, (int[]){tile_min.x, tile_min.x
			+ TILE}, (int[]){base.x, base.x + cub->minimap.tilesize});
	line.crd.y0 = map((int)cub->player.pos.y, (int[]){tile_min.y, tile_min.y
			+ TILE}, (int[]){base.y, base.y + cub->minimap.tilesize});
	line.crd.x = line.crd.x0 + cub->player.dir.x * 10;
	line.crd.y = line.crd.y0 + cub->player.dir.y * 10;
	bresenham_line(line);
	line.crd.x0++;
	line.crd.x++;
	bresenham_line(line);
	line.crd.y0++;
	line.crd.y++;
	bresenham_line(line);
	init_circle(&circle, --line.crd.x0, --line.crd.y0, 3);
	bresenham_circle(circle);
}
