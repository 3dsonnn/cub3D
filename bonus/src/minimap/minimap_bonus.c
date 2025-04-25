/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 22:59:10 by efinda            #+#    #+#             */
/*   Updated: 2025/04/24 10:15:02 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static void	paint_minimap_tile(t_cub *cub, t_plane edges, t_point iter,
		int color)
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

static void	paint_obx(t_cub *cub, t_tile *topleft, t_point *minip)
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
				minip->x = pos.x * cub->minimap.tilesize;
				minip->y = pos.y * cub->minimap.tilesize;
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

static void	paint_nobx(t_cub *cub, int i, int j)
{
	i = -1;
	while (++i < cub->scene.map.size.y)
	{
		j = -1;
		while (++j < cub->scene.map.size.x)
			paint_minimap_tile(cub, (t_plane){0, ((j + 1)
					* cub->minimap.tilesize), (i * cub->minimap.tilesize), ((i
						+ 1) * cub->minimap.tilesize)}, (t_point){j, i},
				cub->minimap.tiles[i][j].color);
	}
}

void	minimap(t_cub *cub)
{
	t_point	minip;

	if (cub->minimap.box)
	{
		// ft_printf("%d\n", cub->minimap.bounds.x);
		my_mlx_resize_img(cub->mlx, &cub->minimap.img,
			(t_point){cub->minimap.tilesize * (cub->minimap.bounds.x + 1),
			cub->minimap.tilesize * (cub->minimap.bounds.y + 1)});
		paint_obx(cub, cub->minimap.corners[TOPLEFT], &minip);
		miniplayer(cub, (t_point){minip.x, minip.y},
			(t_point){((int)cub->player.pos.x / TILE) * TILE,
			((int)cub->player.pos.y / TILE) * TILE});
	}
	else
	{
		// paint_nobx(cub, -1, -1);
		miniplayer(cub, (t_point){cub->minimap.cur->crd.x
			* cub->minimap.tilesize, cub->minimap.cur->crd.y
			* cub->minimap.tilesize}, (t_point){((int)cub->player.pos.x
				/ TILE) * TILE, ((int)cub->player.pos.y / TILE) * TILE});
	}
}
