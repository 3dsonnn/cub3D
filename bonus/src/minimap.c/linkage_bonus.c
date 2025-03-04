/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkage_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:09:38 by efinda            #+#    #+#             */
/*   Updated: 2025/03/04 19:42:55 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static void	link_horizontal_boundary_tiles(t_cub *cub, int j)
{
	while (++j < cub->scene.map.size.x)
	{
		cub->minimap.tiles[0][j].down = &cub->minimap.tiles[1][j];
		cub->minimap.tiles[cub->scene.map.size.y
			- 1][j].up = &cub->minimap.tiles[cub->scene.map.size.y - 2][j];
		if (j != 0)
		{
			cub->minimap.tiles[0][j].left = &cub->minimap.tiles[0][j - 1];
			cub->minimap.tiles[cub->scene.map.size.y
				- 1][j].left = &cub->minimap.tiles[cub->scene.map.size.y - 1][j
				- 1];
		}
		if (j != cub->scene.map.size.x - 1)
		{
			cub->minimap.tiles[0][j].right = &cub->minimap.tiles[0][j + 1];
			cub->minimap.tiles[cub->scene.map.size.y
				- 1][j].right = &cub->minimap.tiles[cub->scene.map.size.y - 1][j
				+ 1];
		}
	}
}

static void	link_vertical_boundary_tiles(t_cub *cub, int i)
{
	while (++i < cub->scene.map.size.y)
	{
		cub->minimap.tiles[i][0].right = &cub->minimap.tiles[i][1];
		cub->minimap.tiles[i][cub->scene.map.size.x
			- 1].left = &cub->minimap.tiles[i][cub->scene.map.size.x - 2];
		if (i != 0)
		{
			cub->minimap.tiles[i][0].up = &cub->minimap.tiles[i - 1][0];
			cub->minimap.tiles[i][cub->scene.map.size.x
				- 1].up = &cub->minimap.tiles[i - 1][cub->scene.map.size.x - 1];
		}
		if (i != cub->scene.map.size.y - 1)
		{
			cub->minimap.tiles[i][0].down = &cub->minimap.tiles[i + 1][0];
			cub->minimap.tiles[i][cub->scene.map.size.x
				- 1].down = &cub->minimap.tiles[i + 1][cub->scene.map.size.x
				- 1];
		}
	}
	link_horizontal_boundary_tiles(cub, -1);
}

void	link_tiles(t_cub *cub, int i, int j)
{
	link_vertical_boundary_tiles(cub, -1);
	while (++i < cub->scene.map.size.y - 1)
	{
		j = 0;
		while (++j < cub->scene.map.size.x - 1)
		{
			cub->minimap.tiles[i][j].up = &cub->minimap.tiles[i - 1][j];
			cub->minimap.tiles[i][j].down = &cub->minimap.tiles[i + 1][j];
			cub->minimap.tiles[i][j].left = &cub->minimap.tiles[i][j - 1];
			cub->minimap.tiles[i][j].right = &cub->minimap.tiles[i][j + 1];
		}
	}
}
