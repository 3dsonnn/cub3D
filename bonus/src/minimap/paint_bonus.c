/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 22:57:45 by efinda            #+#    #+#             */
/*   Updated: 2025/04/02 03:35:17 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

void	paint_minimap_tile(t_cub *cub, t_plane edges, t_point iter, int color)
{
	while (edges.y0 < edges.y)
	{
		edges.x0 = iter.x * cub->minimap.tilesize;
		while (edges.x0 < edges.x)
		{
			if (color == TRANSPARENT)
				my_mlx_pixel_put(&cub->minimap.img, edges.x0, edges.y0,
					my_mlx_get_pixel(cub->img, edges.x0 + 10, edges.y0 + 10));
			else if (edges.x0 == iter.x * cub->minimap.tilesize
				|| edges.x0 == edges.x - 1 || edges.y0 == iter.y
				* cub->minimap.tilesize || edges.y0 == edges.y - 1)
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

void	paint_obx(t_cub *cub, t_tile *topleft, t_point *minip)
{
	t_tile	*tmp;
	t_point	pos;

	pos = (t_point){-1, -1};
	while (++(pos.y) < cub->minimap.bounds.y + 1)
	{
		pos.x = -1;
		tmp = topleft;
		while (++(pos.x) < cub->minimap.bounds.x + 1)
		{
			if (tmp->id == 'C')
			{
				minip->x = pos.x * cub->minimap.tilesize + 10;
				minip->y = pos.y * cub->minimap.tilesize + 10;
			}
			paint_minimap_tile(cub, (t_plane){0, ((pos.x + 1)
					* cub->minimap.tilesize), (pos.y * cub->minimap.tilesize),
				((pos.y + 1) * cub->minimap.tilesize)}, (t_point){pos.x, pos.y},
				tmp->color);
			tmp = tmp->right;
		}
		topleft = topleft->down;
	}
}
