/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 02:08:03 by efinda            #+#    #+#             */
/*   Updated: 2025/02/10 15:12:50 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	set_tiles(t_cub *cub, int i, int j)
{
	while (++i < cub->scene.map.size.y)
	{
		j = -1;
		while (++j < cub->scene.map.size.x)
		{
			cub->minimap.tiles[i][j].crd.x = j;
			cub->minimap.tiles[i][j].crd.y = i;
			cub->minimap.tiles[i][j].id = &cub->scene.map.content[i][j];
			if (cub->scene.map.content[i][j] == '1')
				cub->minimap.tiles[i][j].color = BLUE;
			else
				cub->minimap.tiles[i][j].color = WHITE;
			if (cub->scene.map.content[i][j] == cub->scene.map.start)
			{
				*(cub->minimap.tiles[i][j].id) = 'E';
				cub->cur = &cub->minimap.tiles[i][j];
			}
		}
	}
	update_corners(cub);
}

static void	get_tile_size(t_cub *cub)
{
	int	max;

	cub->minimap.corners[TOPLEFT] = NULL;
	cub->minimap.corners[TOPRIGHT] = NULL;
	cub->minimap.corners[BOTTLEFT] = NULL;
	cub->minimap.corners[BOTTRIGHT] = NULL;
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
}

void	init_minimap(t_cub *cub, int i, int j)
{
	get_tile_size(cub);
	cub->minimap.tiles = (t_tile **)malloc(sizeof(t_tile *)
			* (cub->scene.map.size.y));
	while (++i < cub->scene.map.size.y)
	{
		cub->minimap.tiles[i] = (t_tile *)malloc(sizeof(t_tile)
				* cub->scene.map.size.x);
		j = -1;
		while (++j < cub->scene.map.size.x)
		{
			cub->minimap.tiles[i][j].up = NULL;
			cub->minimap.tiles[i][j].down = NULL;
			cub->minimap.tiles[i][j].left = NULL;
			cub->minimap.tiles[i][j].right = NULL;
			cub->minimap.tiles[i][j].upleft = NULL;
			cub->minimap.tiles[i][j].upright = NULL;
			cub->minimap.tiles[i][j].downleft = NULL;
			cub->minimap.tiles[i][j].downright = NULL;
		}
	}
	link_tiles(cub, 0, 0);
	set_tiles(cub, -1, -1);
	//ft_mtxfree(&cub->scene.map.content);
}
