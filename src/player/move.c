/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 01:25:03 by efinda            #+#    #+#             */
/*   Updated: 2025/02/10 15:17:25 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	move_player_up(t_cub *cub, t_dplane new_pos, int i, int j)
{
	new_pos.x0 += round(SPEED * cub->player.dir.x);
	new_pos.y0 += round(SPEED * cub->player.dir.y);
	if (same_tile(cub, cub->cur, new_pos.x0, new_pos.y0))
	{
		cub->player.pos.x0 = new_pos.x0;
		cub->player.pos.y0 = new_pos.y0;
		return ;
	}
	while (++i < 8)
	{
		if (cub->player.neighbors[i] && same_tile(cub, cub->player.neighbors[i], new_pos.x0, new_pos.y0))
		{
			if (*(cub->player.neighbors[i]->id) == '1')
				return ;
			j = i;
		}
	}
	cub->player.pos.x0 = new_pos.x0;
	cub->player.pos.y0 = new_pos.y0;
	*(cub->player.neighbors[j]->id) = 'E';
	*(cub->cur->id) = '0';
	cub->cur = cub->player.neighbors[j];
	update_neighbors(cub);
	update_bounding_box(cub);
}

static void	move_player_down(t_cub *cub, t_dplane new_pos, int i, int j)
{
	new_pos.x0 -= round(SPEED * cub->player.dir.x);
	new_pos.y0 -= round(SPEED * cub->player.dir.y);
	if (same_tile(cub, cub->cur, new_pos.x0, new_pos.y0))
	{
		cub->player.pos.x0 = new_pos.x0;
		cub->player.pos.y0 = new_pos.y0;
		return ;
	}
	while (++i < 8)
	{
		if (cub->player.neighbors[i] && same_tile(cub, cub->player.neighbors[i], new_pos.x0, new_pos.y0))
		{
			if (*(cub->player.neighbors[i]->id) == '1')
				return ;
			j = i;
		}
	}
	cub->player.pos.x0 = new_pos.x0;
	cub->player.pos.y0 = new_pos.y0;
	*(cub->player.neighbors[j]->id) = 'E';
	*(cub->cur->id) = '0';
	cub->cur = cub->player.neighbors[j];
	update_neighbors(cub);
	update_bounding_box(cub);
}

static void	move_player_right(t_cub *cub, t_dplane new_pos, int i, int j)
{
	new_pos.x0 -= round(SPEED * cub->player.dir.x0);
	new_pos.y0 -= round(SPEED * cub->player.dir.y0);
	if (same_tile(cub, cub->cur, new_pos.x0, new_pos.y0))
	{
		cub->player.pos.x0 = new_pos.x0;
		cub->player.pos.y0 = new_pos.y0;
		return ;
	}
	while (++i < 8)
	{
		if (cub->player.neighbors[i] && same_tile(cub, cub->player.neighbors[i], new_pos.x0, new_pos.y0))
		{
			if (*(cub->player.neighbors[i]->id) == '1')
				return ;
			j = i;
		}
	}
	cub->player.pos.x0 = new_pos.x0;
	cub->player.pos.y0 = new_pos.y0;
	*(cub->player.neighbors[j]->id) = 'E';
	*(cub->cur->id) = '0';
	cub->cur = cub->player.neighbors[j];
	update_neighbors(cub);
	update_bounding_box(cub);
}

static void	move_player_left(t_cub *cub, t_dplane new_pos, int i, int j)
{
	new_pos.x0 += round(SPEED * cub->player.dir.x0);
	new_pos.y0 += round(SPEED * cub->player.dir.y0);
	if (same_tile(cub, cub->cur, new_pos.x0, new_pos.y0))
	{
		cub->player.pos.x0 = new_pos.x0;
		cub->player.pos.y0 = new_pos.y0;
		return ;
	}
	while (++i < 8)
	{
		if (cub->player.neighbors[i] && same_tile(cub, cub->player.neighbors[i], new_pos.x0, new_pos.y0))
		{
			if (*(cub->player.neighbors[i]->id) == '1')
				return ;
			j = i;
		}
	}
	cub->player.pos.x0 = new_pos.x0;
	cub->player.pos.y0 = new_pos.y0;
	*(cub->player.neighbors[j]->id) = 'E';
	*(cub->cur->id) = '0';
	cub->cur = cub->player.neighbors[j];
	update_neighbors(cub);
	update_bounding_box(cub);
}

void	move_player(t_cub *cub, t_plane flag)
{
	if (flag.x0)
		move_player_up(cub, cub->player.pos, -1, -1);
	else if (flag.x)
		move_player_down(cub, cub->player.pos, -1, -1);
	else if (flag.y0)
		move_player_right(cub, cub->player.pos, -1, -1);
	else if (flag.y)
		move_player_left(cub, cub->player.pos, -1, -1);
}
