/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 01:16:17 by efinda            #+#    #+#             */
/*   Updated: 2025/02/20 13:43:27 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	get_starting_angle(t_cub *cub, char spawning_orientation)
{
	if ('N' == spawning_orientation)
		cub->player.angle = DEG_TO_RAD(270.0);
	else if ('S' == spawning_orientation)
		cub->player.angle = DEG_TO_RAD(90.0);
	else if ('E' == spawning_orientation)
		cub->player.angle = DEG_TO_RAD(0.0);
	else if ('W' == spawning_orientation)
		cub->player.angle = DEG_TO_RAD(180.0);
}

void	init_player(t_cub *cub)
{
	cub->player.pos.x = (cub->scene.map.spos.x * TILE) + (TILE / 2);
	cub->player.pos.y = (cub->scene.map.spos.y * TILE) + (TILE / 2);
	get_starting_angle(cub, cub->scene.map.start);
	rotate_player(cub, -1);
}
