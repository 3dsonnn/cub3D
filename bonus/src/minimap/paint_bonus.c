/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 22:57:45 by efinda            #+#    #+#             */
/*   Updated: 2025/03/06 00:56:32 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

void	paint_minimap_tile(t_cub *cub, int i, int j, int color)
{
	int	x0;
	int	x;
	int	y0;
	int	y;

	y0 = i * cub->minimap.tilesize;
	x = (j + 1) * cub->minimap.tilesize;
	y = (i + 1) * cub->minimap.tilesize;
	while (y0 < y)
	{
		x0 = j * cub->minimap.tilesize;
		while (x0 < x)
		{
			if (x0 == j * cub->minimap.tilesize || x0 == x - 1 || y0 == i
				* cub->minimap.tilesize || y0 == y - 1)
				my_mlx_pixel_put(&cub->img, x0, y0, 0xFFFFFF);
			else
				my_mlx_pixel_put(&cub->img, x0, y0, color);
			x0++;
		}
		y0++;
	}
}

void	paint_obx(t_cub *cub, t_tile *topleft)
{
	t_tile *tmp;
	t_point pos;

	pos = (t_point){-1, -1};
	while (++(pos.y) < 11)
	{
		pos.x = -1;
		tmp = topleft;
		while (++(pos.x) < 11)
		{
			if (tmp->id == ' ')
				;
			else
				paint_minimap_tile(cub, pos.y, pos.x, tmp->color);
			tmp = tmp->right;
		}
		topleft = topleft->down;
	}
}
