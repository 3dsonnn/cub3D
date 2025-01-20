/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players_movements_0.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 01:25:03 by efinda            #+#    #+#             */
/*   Updated: 2025/01/20 03:04:37 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	move_player_up(t_cub *cub)
{
	if (cub->player.pos.y0 - cub->player.size.y <= cub->player.tile->up->pos.y)
	{
		if (cub->player.tile->up->id != '1')
		{
			cub->player.pos.y0 -= cub->player.size.y;
			cub->player.pos.y -= cub->player.size.y;
			cub->player.tile->up->id = 'E';
			cub->player.tile->id = '\0';
			cub->player.tile = cub->player.tile->up;
		}
	}
	else
	{
		cub->player.pos.y0 -= cub->player.size.y;
		cub->player.pos.y -= cub->player.size.y;
	}
}

static void	move_player_down(t_cub *cub)
{
	if (cub->player.pos.y
		+ cub->player.size.y >= cub->player.tile->down->pos.y0)
	{
		if (cub->player.tile->down->id != '1')
		{
			cub->player.pos.y0 += cub->player.size.y;
			cub->player.pos.y += cub->player.size.y;
			cub->player.tile->down->id = 'E';
			cub->player.tile->id = '\0';
			cub->player.tile = cub->player.tile->down;
		}
	}
	else
	{
		cub->player.pos.y0 += cub->player.size.y;
		cub->player.pos.y += cub->player.size.y;
	}
}

static void	move_player_right(t_cub *cub)
{
	if (cub->player.pos.x
		+ cub->player.size.x >= cub->player.tile->right->pos.x0)
	{
		if (cub->player.tile->right->id != '1')
		{
			cub->player.pos.x0 += cub->player.size.x;
			cub->player.pos.x += cub->player.size.x;
			cub->player.tile->right->id = 'E';
			cub->player.tile->id = '\0';
			cub->player.tile = cub->player.tile->right;
		}
	}
	else
	{
		cub->player.pos.x0 += cub->player.size.x;
		cub->player.pos.x += cub->player.size.x;
	}
}

static void	move_player_left(t_cub *cub)
{
	if (cub->player.pos.x0
		- cub->player.size.x <= cub->player.tile->left->pos.x)
	{
		if (cub->player.tile->left->id != '1')
		{
			cub->player.pos.x0 -= cub->player.size.x;
			cub->player.pos.x -= cub->player.size.x;
			cub->player.tile->left->id = 'E';
			cub->player.tile->id = '\0';
			cub->player.tile = cub->player.tile->left;
		}
	}
	else
	{
		cub->player.pos.x0 -= cub->player.size.x;
		cub->player.pos.x -= cub->player.size.x;
	}
}

void	move_player(t_cub *cub, t_plane flag)
{
	if (check_players_newpos_overlap(cub, flag))
		return ;
	if (flag.x0)
		move_player_up(cub);
	else if (flag.x)
		move_player_down(cub);
	else if (flag.y0)
		move_player_right(cub);
	else if (flag.y)
		move_player_left(cub);
}
