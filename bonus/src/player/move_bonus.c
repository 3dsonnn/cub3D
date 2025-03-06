/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 01:25:03 by efinda            #+#    #+#             */
/*   Updated: 2025/03/06 03:06:52 by efinda           ###   ########.fr       */
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
	cub->minimap.cur->color = WHITE;
	cub->minimap.cur = &cub->minimap.tiles[i][j];
	cub->minimap.cur->id = 'C';
	cub->minimap.cur->color = RED;
	update_obx(cub, cub->minimap.cur, (t_plane){0, 0, 0, 0}, (t_iter){-1, -1,
		-1, -1, -1, -1});
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
	update_cur_tile(cub, new_pos.x, new_pos.y);
	cub->player.pos.x = new_pos.x;
	cub->player.pos.y = new_pos.y;
}
