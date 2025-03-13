/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 01:25:03 by efinda            #+#    #+#             */
/*   Updated: 2025/03/13 08:42:00 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static void	update_cur_tile(t_cub *cub, double x, double y)
{
	int	i;
	int	j;

	i = (int)floor(y / TILE);
	j = (int)floor(x / TILE);
	cub->minimap.cur->id = '0';
	cub->minimap.cur = &cub->minimap.tiles[i][j];
	cub->minimap.cur->id = 'C';
	update_obx(cub);
}

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
			cub->player.pos.x += cub->player.plane.x * SPEED * strafe;
			cub->player.pos.y += cub->player.plane.y * SPEED * strafe;
		}
	}
	if (cub->minimap.cur != &cub->minimap.tiles[(int)floor(cub->player.pos.y
			/ TILE)][(int)floor(cub->player.pos.x / TILE)])
		update_cur_tile(cub, cub->player.pos.x, cub->player.pos.y);
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
