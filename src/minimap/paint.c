/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 22:30:48 by efinda            #+#    #+#             */
/*   Updated: 2025/02/08 22:41:06 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	paint_minitile(t_cub *cub, int i, int j, int color)
{
	int	x0;
	int	x;
	int	y0;
	int	y;

	y0 = i * cub->minimap.tilesize + 10;
	x = (j + 1) * cub->minimap.tilesize + 10;
	y = (i + 1) * cub->minimap.tilesize + 10;
	while (y0 < y)
	{
		x0 = j * cub->minimap.tilesize + 10;
		while (x0 < x)
		{
			if (x0 == j * cub->minimap.tilesize || x0 == x - 1 || y0 == i
				* cub->minimap.tilesize || y0 == y - 1)
				my_mlx_pixel_put(&cub->img, x0, y0, WHITE);
			else
				my_mlx_pixel_put(&cub->img, x0, y0, color);
			x0++;
		}
		y0++;
	}
}

void	paint_box(t_cub *cub, t_tile *topleft)
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
			if (tmp->id != ' ')
				paint_minitile(cub, pos.y, pos.x, tmp->color);
			tmp = tmp->right;
		}
		topleft = topleft->down;
	}
}

void	paint(t_cub *cub, int i, int j)
{
	while (++i < cub->scene.map.size.y)
	{
		j = -1;
		while (++j < cub->scene.map.size.x)
		{
			if (cub->minimap.tiles[i][j].id != ' ')
				paint_minitile(cub, i, j, cub->minimap.tiles[i][j].color);
		}
	}
}
