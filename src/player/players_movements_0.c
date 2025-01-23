/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players_movements_0.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 01:25:03 by efinda            #+#    #+#             */
/*   Updated: 2025/01/23 07:23:54 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	move_player_up(t_cub *cub, int i)
{
	t_tile	*neighbors[] = {cub->player.tile->up, cub->player.tile->upleft,
			cub->player.tile->upright, cub->player.tile->down,
			cub->player.tile->downleft, cub->player.tile->downright,
			cub->player.tile->left, cub->player.tile->right};

	cub->player.pos.x0 += (int)round(cub->player.size.x * cub->player.dir.x);
	cub->player.pos.y0 += (int)round(cub->player.size.y * cub->player.dir.y);
	while (++i < 8)
	{
		if (neighbors[i] && check_if_same_tile(neighbors[i]->pos,
				neighbors[i]->pos.x0, cub->player.pos.x0, cub->player.pos.y0))
		{
			neighbors[i]->id = 'E';
			cub->player.tile->id = '\0';
			cub->player.tile = neighbors[i];
		}
	}
}

static void	move_player_down(t_cub *cub, int i)
{
	t_tile	*neighbors[] = {cub->player.tile->up, cub->player.tile->upleft,
			cub->player.tile->upright, cub->player.tile->down,
			cub->player.tile->downleft, cub->player.tile->downright,
			cub->player.tile->left, cub->player.tile->right};

	cub->player.pos.x0 -= (int)round(cub->player.size.x * cub->player.dir.x);
	cub->player.pos.y0 -= (int)round(cub->player.size.y * cub->player.dir.y);
	while (++i < 8)
	{
		if (neighbors[i] && check_if_same_tile(neighbors[i]->pos,
				neighbors[i]->pos.x0, cub->player.pos.x0, cub->player.pos.y0))
		{
			neighbors[i]->id = 'E';
			cub->player.tile->id = '\0';
			cub->player.tile = neighbors[i];
		}
	}
}

static void	move_player_right(t_cub *cub, int i)
{
	t_tile	*neighbors[] = {cub->player.tile->up, cub->player.tile->upleft,
			cub->player.tile->upright, cub->player.tile->down,
			cub->player.tile->downleft, cub->player.tile->downright,
			cub->player.tile->left, cub->player.tile->right};

	cub->player.pos.x0 -= (int)round(cub->player.size.x * cub->player.dir.x0);
	cub->player.pos.y0 -= (int)round(cub->player.size.y * cub->player.dir.y0);
	while (++i < 8)
	{
		if (neighbors[i] && check_if_same_tile(neighbors[i]->pos,
				neighbors[i]->pos.x0, cub->player.pos.x0, cub->player.pos.y0))
		{
			neighbors[i]->id = 'E';
			cub->player.tile->id = '\0';
			cub->player.tile = neighbors[i];
		}
	}
}

static void	move_player_left(t_cub *cub, int i)
{
	t_tile	*neighbors[] = {cub->player.tile->up, cub->player.tile->upleft,
			cub->player.tile->upright, cub->player.tile->down,
			cub->player.tile->downleft, cub->player.tile->downright,
			cub->player.tile->left, cub->player.tile->right};

	cub->player.pos.x0 += (int)round(cub->player.size.x * cub->player.dir.x0);
	cub->player.pos.y0 += (int)round(cub->player.size.y * cub->player.dir.y0);
	while (++i < 8)
	{
		if (neighbors[i] && check_if_same_tile(neighbors[i]->pos,
				neighbors[i]->pos.x0, cub->player.pos.x0, cub->player.pos.y0))
		{
			neighbors[i]->id = 'E';
			cub->player.tile->id = '\0';
			cub->player.tile = neighbors[i];
		}
	}
}

void	move_player(t_cub *cub, t_plane flag)
{
	if (check_players_newpos_overlap(cub, flag))
	{
		cub->flag = 0;
		return ;
	}
	cub->flag = 1;
	if (flag.x0)
		move_player_up(cub, -1);
	else if (flag.x)
		move_player_down(cub, -1);
	else if (flag.y0)
		move_player_right(cub, -1);
	else if (flag.y)
		move_player_left(cub, -1);
}
