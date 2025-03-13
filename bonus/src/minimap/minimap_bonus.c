/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 22:59:10 by efinda            #+#    #+#             */
/*   Updated: 2025/03/13 08:52:25 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static void	paint_nobx(t_cub *cub, int i, int j)
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
				paint_minimap_tile(cub, i, j, cub->minimap.tiles[i][j].color);
		}
	}
}

void	minimap(t_cub *cub)
{
	t_point	minip;

	if (cub->minimap.box)
	{
		paint_obx(cub, cub->minimap.corners[TOPLEFT], &minip);
		miniplayer(cub, (t_point){minip.x, minip.y},
			(t_point){((int)cub->player.pos.x / TILE) * TILE,
			((int)cub->player.pos.y / TILE) * TILE});
	}
	else
	{
		paint_nobx(cub, -1, -1);
		miniplayer(cub, (t_point){cub->minimap.cur->crd.x
			* cub->minimap.tilesize + 10, cub->minimap.cur->crd.y
			* cub->minimap.tilesize + 10}, (t_point){((int)cub->player.pos.x
				/ TILE) * TILE, ((int)cub->player.pos.y / TILE) * TILE});
	}
}
