/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 01:16:17 by efinda            #+#    #+#             */
/*   Updated: 2025/02/10 15:14:02 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	get_starting_angle(t_cub *cub, char spawning_orientation)
{
	if ('E' == spawning_orientation)
		cub->player.angle = DEG_TO_RAD(0.0);
	else if ('N' == spawning_orientation)
		cub->player.angle = DEG_TO_RAD(90.0);
	else if ('W' == spawning_orientation)
		cub->player.angle = DEG_TO_RAD(180.0);
	else if ('S' == spawning_orientation)
		cub->player.angle = DEG_TO_RAD(270.0);
}

void	init_player(t_cub *cub)
{
	cub->player.size = (int)floor(cub->minimap.tilesize / 10);
	cub->player.pos.x0 = floor((cub->scene.map.spos.x * cub->minimap.tilesize)
			- ((cub->scene.map.spos.x * cub->minimap.tilesize
					- ((cub->scene.map.spos.x - 1) * cub->minimap.tilesize))
				/ 2));
	cub->player.pos.y0 = floor((cub->scene.map.spos.y * cub->minimap.tilesize)
			- ((cub->scene.map.spos.y * cub->minimap.tilesize
					- ((cub->scene.map.spos.y - 1) * cub->minimap.tilesize))
				/ 2));
	get_starting_angle(cub, cub->scene.map.start);
	update_neighbors(cub);
	rotate_player(cub, -1);
}
