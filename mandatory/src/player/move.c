/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 01:25:03 by efinda            #+#    #+#             */
/*   Updated: 2025/03/06 10:46:04 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	move_player(t_cub *cub, double forward, double strafe, t_dpoint new_pos)
{
	if (forward)
	{
		new_pos.x += cub->player.dir.x * SPEED * forward;
		new_pos.y += cub->player.dir.y * SPEED * forward;
	}
	if (strafe)
	{
		new_pos.x += cub->player.plane.x * SPEED * strafe;
		new_pos.y += cub->player.plane.y * SPEED * strafe;
	}
	if (!is_wall(cub, new_pos.x, new_pos.y))
		cub->player.pos = new_pos;
}

void	rotate_player(t_cub *cub, int angle_delta)
{
	printf("Angle delta: %.2f, Before angle: %.2f\n", angle_delta, cub->player.angle);
    cub->player.angle += angle_delta;
    angle_delta = ft_normalizer(angle_delta);
	
    cub->player.dir.x = cos(cub->player.angle);
    cub->player.dir.y = sin(cub->player.angle);
    
    cub->player.plane.x = -cub->player.dir.y;
    cub->player.plane.y = cub->player.dir.x;
    
    printf("After - Angle: %.2f, Dir: (%.2f, %.2f), Plane: (%.2f, %.2f)\n",
           cub->player.angle, cub->player.dir.x, cub->player.dir.y,
           cub->player.plane.x, cub->player.plane.y);
}
