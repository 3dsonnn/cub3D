/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:09:47 by efinda            #+#    #+#             */
/*   Updated: 2025/04/02 03:35:05 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static void	set_tiles_aux(t_cub *cub, char c, int i, int j)
{
	if (c == '1')
	{
		cub->minimap.tiles[i][j].id = '1';
		cub->minimap.tiles[i][j].color = BLUE;
	}
	else if (c == '0')
	{
		cub->minimap.tiles[i][j].id = '0';
		cub->minimap.tiles[i][j].color = WHITE;
	}
	else if (c == ' ')
	{
		cub->minimap.tiles[i][j].id = ' ';
		cub->minimap.tiles[i][j].color = TRANSPARENT;
	}
}

void	set_tiles(t_cub *cub, int i, int j)
{
	while (++i < cub->scene.map.size.y)
	{
		j = -1;
		while (++j < cub->scene.map.size.x)
		{
			cub->minimap.tiles[i][j].crd.x = j;
			cub->minimap.tiles[i][j].crd.y = i;
			set_tiles_aux(cub, cub->scene.map.content[i][j], i, j);
			if (i == cub->scene.map.spos.y && j == cub->scene.map.spos.x)
			{
				cub->minimap.tiles[i][j].id = 'C';
				cub->minimap.cur = &cub->minimap.tiles[i][j];
			}
		}
	}
	update_obx(cub, cub->minimap.corners, cub->minimap.tiles);
}
