/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:30:45 by efinda            #+#    #+#             */
/*   Updated: 2025/03/04 19:45:37 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static void	is_obx(t_cub *cub, int max)
{
	if (cub->scene.map.size.x < 11 && cub->scene.map.size.y < 11)
	{
		if (cub->scene.map.size.x > cub->scene.map.size.y)
			max = cub->scene.map.size.x;
		else
			max = cub->scene.map.size.y;
		cub->minimap.tilesize = (int)floor(220 / max);
		cub->minimap.box = 0;
	}
	else
	{
		cub->minimap.tilesize = 20;
		cub->minimap.box = 1;
	}
	cub->minimap.corners[TOPLEFT] = NULL;
	cub->minimap.corners[TOPRIGHT] = NULL;
	cub->minimap.corners[BOTTLEFT] = NULL;
	cub->minimap.corners[BOTTRIGHT] = NULL;
}

void	init_minimap(t_cub *cub, int i, int j)
{
	is_obx(cub, 0);
    cub->minimap.tiles = (t_tile **)malloc(sizeof(t_tile *) * (cub->scene.map.size.y));
    if (!cub->minimap.tiles)
        ;
	while (++i < cub->scene.map.size.y)
	{
		j = -1;
		cub->minimap.tiles[i] = (t_tile *)malloc(sizeof(t_tile) * cub->scene.map.size.x);
		while (++j < cub->scene.map.size.x)
		{
			cub->minimap.tiles[i][j].up = NULL;
			cub->minimap.tiles[i][j].down = NULL;
			cub->minimap.tiles[i][j].left = NULL;
			cub->minimap.tiles[i][j].right = NULL;
		}
	}
	link_tiles(cub, 0, 0);
	set_tiles(cub, -1, -1);
	ft_mtxfree(&cub->scene.map.content);
}
