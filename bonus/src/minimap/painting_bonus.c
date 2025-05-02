/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:11:34 by efinda            #+#    #+#             */
/*   Updated: 2025/04/30 18:04:12 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

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
			tmp = tmp->right;
		}
		topleft = topleft->down;
	}
}
