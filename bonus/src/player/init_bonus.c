/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 01:16:17 by efinda            #+#    #+#             */
/*   Updated: 2025/03/23 16:43:34 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

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
	cub->player.pos.x = (cub->scene.map.spos.x * TILE) + (TILE / 2);
	cub->player.pos.y = (cub->scene.map.spos.y * TILE) + (TILE / 2);
	get_starting_angle(cub, cub->scene.map.start);
	cub->player.dir.x = cos(cub->player.angle);
	cub->player.dir.y = sin(cub->player.angle);
	cub->player.plane.x = -cub->player.dir.y;
	cub->player.plane.y = cub->player.dir.x;
	cub->player.health = (t_nbr){.value = 100, .str = NULL};
	mlx_do_key_autorepeatoff(cub->mlx);
}
