/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:09:47 by efinda            #+#    #+#             */
/*   Updated: 2025/04/26 20:33:26 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static void	set_tile_color(t_cub *cub, t_tile *tile, char c)
{
	if (c == '1')
		tile->color = BLUE;
	else if (c == '0')
		tile->color = WHITE;
	else if (c == ' ')
		tile->color = TRANSPARENT;
	else if (c == 'D')
		tile->color = DARK_GRAY;
	else if (c == '!')
		tile->color = GREEN;
	else
		tile->color = WHITE;
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
			cub->minimap.tiles[i][j].id = cub->scene.map.content[i][j];
			set_tile_color(cub, &cub->minimap.tiles[i][j], cub->scene.map.content[i][j]);
			if (i == cub->scene.map.spos.y && j == cub->scene.map.spos.x)
				cub->minimap.cur = &cub->minimap.tiles[i][j];
		}
	}
	update_obx(cub, cub->minimap.corners, cub->minimap.tiles);
}
