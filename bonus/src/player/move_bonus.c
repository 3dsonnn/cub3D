/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 01:25:03 by efinda            #+#    #+#             */
/*   Updated: 2025/03/04 17:31:31 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

void	move_player(t_cub *cub, t_dpoint new_pos, t_plane flag)
{
	if (flag.x0)
	{
		new_pos.y += round(SPEED * cub->player.dir.y);
		new_pos.x += round(SPEED * cub->player.dir.x);
	}
	else if (flag.x)
	{
		new_pos.x -= round(SPEED * cub->player.dir.x);
		new_pos.y -= round(SPEED * cub->player.dir.y);
	}
	else if (flag.y0)
	{
		new_pos.x -= round(SPEED * cub->player.dir.x0);
		new_pos.y -= round(SPEED * cub->player.dir.y0);
	}
	else if (flag.y)
	{
		new_pos.x += round(SPEED * cub->player.dir.x0);
		new_pos.y += round(SPEED * cub->player.dir.y0);
	}
	if (is_wall(cub, new_pos.x, new_pos.y))
		return ;
	cub->player.pos.x = new_pos.x;
	cub->player.pos.y = new_pos.y;
}
