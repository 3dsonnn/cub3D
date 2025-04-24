/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 01:16:17 by efinda            #+#    #+#             */
/*   Updated: 2025/04/23 19:06:49 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	get_starting_angle(t_cub *cub, char spawning_orientation)
{
	if (spawning_orientation == 'N')
		cub->player.angle = (270.0 * (M_PI / 180.0));
	else if (spawning_orientation == 'S')
		cub->player.angle = (90.0 * (M_PI / 180.0));
	else if (spawning_orientation == 'E')
		cub->player.angle = (0.0 * (M_PI / 180.0));
	else if (spawning_orientation == 'W')
		cub->player.angle = (180.0 * (M_PI / 180.0));
}

void	init_player(t_cub *cub)
{
	cub->player.pos = (t_dpoint){.x = (cub->scene.map.spos.x * TILE) + (TILE
			/ 2), .y = (cub->scene.map.spos.y * TILE) + (TILE / 2)};
	get_starting_angle(cub, cub->scene.map.start);
	cub->player.dir = (t_dpoint){.x = cos(cub->player.angle),
		.y = sin(cub->player.angle)};
	cub->player.plane = (t_dpoint){.x = -cub->player.dir.y,
		.y = cub->player.dir.x};
}
