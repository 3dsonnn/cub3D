/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 22:59:10 by efinda            #+#    #+#             */
/*   Updated: 2025/03/13 02:35:52 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static inline int	map(int old_value, int old_limits[2], int new_limits[2])
{
	double	old_range;
	double	new_range;
	double	ratio;

	old_range = old_limits[1] - old_limits[0];
	new_range = new_limits[1] - new_limits[0];
	ratio = (double)(old_value - old_limits[0]) / old_range;
	return ((int)(new_limits[0] + ratio * new_range));
}

static void	miniplayer(t_cub *cub, t_point base, t_point tile_min)
{
	t_bresenham_line	line;

	line.img = &cub->img;
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
}

void	minimap(t_cub *cub, int i, int j)
{
	if (cub->minimap.box)
		paint_obx(cub, cub->minimap.corners[TOPLEFT]);
	else
	{
		i = -1;
		while (++i < cub->scene.map.size.y)
		{
			j = -1;
			while (++j < cub->scene.map.size.x)
			{
				if (cub->minimap.tiles[i][j].id == ' ')
					;
				else
					paint_minimap_tile(cub, i, j,
						cub->minimap.tiles[i][j].color);
			}
		}
	}
	miniplayer(cub, (t_point){cub->minimap.cur->crd.x * cub->minimap.tilesize
		+ 10, cub->minimap.cur->crd.y * cub->minimap.tilesize + 10},
		(t_point){((int)cub->player.pos.x / TILE) * TILE,
		((int)cub->player.pos.y / TILE) * TILE});
}
