/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 01:16:17 by efinda            #+#    #+#             */
/*   Updated: 2025/03/08 11:21:27 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	get_starting_angle(t_cub *cub, char spawning_orientation)
{
	if (spawning_orientation == 'N')
		cub->player.angle = DEG_TO_RAD(270.0);
	else if (spawning_orientation == 'S')
		cub->player.angle = DEG_TO_RAD(90.0);
	else if (spawning_orientation == 'E')
		cub->player.angle = DEG_TO_RAD(0.0);
	else if (spawning_orientation == 'W')
		cub->player.angle = DEG_TO_RAD(180.0);
}

void	init_player(t_cub *cub)
{
	cub->player.pos.x = (cub->scene.map.spos.x * TILE) + (TILE / 2);
	cub->player.pos.y = (cub->scene.map.spos.y * TILE) + (TILE / 2);
	get_starting_angle(cub, cub->scene.map.start);
	cub->player.dir.x = cos(cub->player.angle);
	cub->player.dir.y = sin(cub->player.angle);
	cub->player.plane.x = -cub->player.dir.y;
	cub->player.plane.y = cub->player.dir.x;
}
