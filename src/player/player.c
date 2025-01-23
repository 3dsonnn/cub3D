/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 01:16:17 by efinda            #+#    #+#             */
/*   Updated: 2025/01/23 16:27:28 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	get_starting_angle(t_cub *cub, char spawning_orientation)
{
	if ('E' == spawning_orientation)
		cub->player.angle = 0;
	else if ('N' == spawning_orientation)
		cub->player.angle = 90;
	else if ('W' == spawning_orientation)
		cub->player.angle = 180;
	else if ('S' == spawning_orientation)
		cub->player.angle = 270;
	cub->player.fov.x = fmod(cub->player.angle - (FOV / 2) + 360.0, 360.0);
	cub->player.fov.y = fmod(cub->player.angle + (FOV / 2), 360.0);
}

void	init_player(t_cub *cub, int i, int j)
{
	cub->player.size.x = (int)floor(cub->minimap.tilewidth / 7);
	cub->player.size.y = (int)floor(cub->minimap.tileheight / 7);
	cub->player.ray_step = FOV / cub->minimap.miniwidth;
	while (++i < cub->scene.map.size.y)
	{
		j = -1;
		while (++j < cub->scene.map.size.x)
		{
			if (cub->minimap.tiles[i][j].id == cub->scene.map.start)
			{
				get_starting_angle(cub, cub->scene.map.start);
				cub->player.pos.x0 = (int)floor(cub->minimap.tiles[i][j].pos.x
						- ((cub->minimap.tiles[i][j].pos.x
								- cub->minimap.tiles[i][j].pos.x0) / 2));
				cub->player.pos.y0 = (int)floor(cub->minimap.tiles[i][j].pos.y
						- ((cub->minimap.tiles[i][j].pos.y
								- cub->minimap.tiles[i][j].pos.y0) / 2));
				cub->player.tile = &cub->minimap.tiles[i][j];
				cub->minimap.tiles[i][j].id = 'E';
				break ;
			}
		}
	}
	rotate_player(cub, -1);
}
