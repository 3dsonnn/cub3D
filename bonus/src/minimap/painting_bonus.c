/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:11:34 by efinda            #+#    #+#             */
/*   Updated: 2025/05/04 13:05:01 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static void	paint_miniplayer(t_cub *cub, t_point middle)
{
	t_bresenham_line	line;
	t_bresenham_circle	circle;

	line = (t_bresenham_line){.color = GREEN, .crd = (t_plane){.x0 = middle.x,
		.x = middle.x + cub->player.dir.x * 10, .y0 = middle.y, .y = middle.y
		+ cub->player.dir.y * 10}, .dir = (t_point){0, 0}, .dist = (t_point){0,
		0}, .error = 0, .img = &cub->minimap.img, .updated_error = 0};
	circle = (t_bresenham_circle){.axis = (t_plane){0, 0, 0, 0},
		.center = (t_point){middle.x, middle.y}, .color = RED,
		.limits = (t_point){.x = -1, .y = 3}, .decision = 3,
		.img = &cub->minimap.img, .radius = 3};
	bresenham_line(line);
	line.crd.x0++;
	line.crd.x++;
	bresenham_line(line);
	line.crd.y0++;
	line.crd.y++;
	bresenham_line(line);
	bresenham_circle(circle);
}

static void	paint_minimap_tile(t_cub *cub, t_plane edges, t_point iter,
		int color)
{
	while (edges.y0 < edges.y)
	{
		edges.x0 = iter.x * MINI_TILE;
		while (edges.x0 < edges.x)
		{
			if (color == (int)TRANSPARENT)
				my_mlx_pixel_put(&cub->minimap.img, edges.x0, edges.y0,
					my_mlx_get_pixel(cub->img, edges.x0 + 10, edges.y0 + 10));
			else if (edges.x0 == iter.x * MINI_TILE || edges.x0 == edges.x - 1
				|| edges.y0 == iter.y * MINI_TILE || edges.y0 == edges.y - 1)
				my_mlx_pixel_put(&cub->minimap.img, edges.x0, edges.y0, WHITE);
			else
				my_mlx_pixel_put(&cub->minimap.img, edges.x0, edges.y0,
					my_mlx_get_transparent_color(my_mlx_get_pixel(cub->img,
							edges.x0 + 10, edges.y0 + 10), color, .5));
			edges.x0++;
		}
		edges.y0++;
	}
}

void	paint_minimap(t_cub *cub, t_tile *topleft)
{
	t_tile	*tmp;
	t_point	pos;

	pos = (t_point){-1, -1};
	while (++(pos.y) < 11)
	{
		pos.x = -1;
		tmp = topleft;
		while (++(pos.x) < 11)
		{
			paint_minimap_tile(cub, (t_plane){0, ((pos.x + 1) * MINI_TILE),
				(pos.y * MINI_TILE), ((pos.y + 1) * MINI_TILE)},
				(t_point){pos.x, pos.y}, tmp->color);
			if (tmp == cub->minimap.cur)
				paint_miniplayer(cub, (t_point){(pos.x * MINI_TILE) + (MINI_TILE
						/ 2), (pos.y * MINI_TILE) + (MINI_TILE / 2)});
			tmp = tmp->right;
		}
		topleft = topleft->down;
	}
}
