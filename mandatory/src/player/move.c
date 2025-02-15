/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 01:25:03 by efinda            #+#    #+#             */
/*   Updated: 2025/02/15 15:18:22 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static int	is_wall(t_cub *cub, double x, double y)
{
	int	i;
	int	j;

	if (x < 0 || x >= cub->scene.map.size.x * TILE || y < 0
		|| y >= cub->scene.map.size.y * TILE)
		return (1);
	i = (int)floor(y / TILE);
	j = (int)floor(x / TILE);
	if (i < 0 || i > cub->scene.map.size.y - 1 || j < 0
		|| j > cub->scene.map.size.x - 1 || cub->scene.map.content[i][j] == '1')
		return (1);
	return (0);
}

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
