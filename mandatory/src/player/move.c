/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 01:25:03 by efinda            #+#    #+#             */
/*   Updated: 2025/03/09 01:17:43 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	move_player(t_cub *cub, double forward, double strafe, t_dpoint new_pos)
{
	if (forward)
	{
		new_pos.x += cub->player.dir.x * (SPEED + 10) * forward;
		new_pos.y += cub->player.dir.y * (SPEED + 10) * forward;
		if (!is_wall(cub, new_pos.x, new_pos.y))
		{
			cub->player.pos.x += cub->player.dir.x * SPEED * forward;
			cub->player.pos.y += cub->player.dir.y * SPEED * forward;
		}
	}
	if (strafe)
	{
		new_pos.x += cub->player.plane.x * (SPEED + 10) * strafe;
		new_pos.y += cub->player.plane.y * (SPEED + 10) * strafe;
		if (!is_wall(cub, new_pos.x, new_pos.y))
		{
			cub->player.pos.x += cub->player.dir.x * SPEED * strafe;
			cub->player.pos.y += cub->player.dir.y * SPEED * strafe;
		}
	}
}

void	rotate_player(t_cub *cub, double angle_delta)
{
	cub->player.angle += angle_delta;
	cub->player.angle = ft_normalizer(cub->player.angle);
	cub->player.dir.x = cos(cub->player.angle);
	cub->player.dir.y = sin(cub->player.angle);
	cub->player.plane.x = -cub->player.dir.y;
	cub->player.plane.y = cub->player.dir.x;
}
