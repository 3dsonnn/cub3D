/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players_movements_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:07:49 by efinda            #+#    #+#             */
/*   Updated: 2025/01/20 02:58:38 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static int	check_player(t_plane tile, int tilex0, t_plane pos, int posx0)
{
	int	x;
	int	y;

	while (tile.y0 < tile.y)
	{
		tile.x0 = tilex0 - 1;
		while (++tile.x0 < tile.x)
		{
			y = pos.y0 - 1;
			while (++y < pos.y)
			{
				x = posx0 - 1;
				while (++x < pos.x)
					if (tile.x0 == x && tile.y0 == y)
						return (1);
			}
		}
		tile.y0++;
	}
	return (0);
}

int	check_player_up(t_cub *cub)
{
	get_ifpos(cub);
	if (cub->player.tile->upleft->id == '1'
		&& check_player(cub->player.tile->upleft->pos,
			cub->player.tile->upleft->pos.x0, cub->player.ifpos[IFUP],
			cub->player.ifpos[IFUP].x0))
		return (1);
	if (cub->player.tile->up->id == '1'
		&& check_player(cub->player.tile->up->pos, cub->player.tile->up->pos.x0,
			cub->player.ifpos[IFUP], cub->player.ifpos[IFUP].x0))
		return (1);
	if (cub->player.tile->upright->id == '1'
		&& check_player(cub->player.tile->upright->pos,
			cub->player.tile->upright->pos.x0, cub->player.ifpos[IFUP],
			cub->player.ifpos[IFUP].x0))
		return (1);
	return (0);
}

int	check_player_down(t_cub *cub)
{
	get_ifpos(cub);
	if (cub->player.tile->downleft->id == '1'
		&& check_player(cub->player.tile->downleft->pos,
			cub->player.tile->downleft->pos.x0, cub->player.ifpos[IFDOWN],
			cub->player.ifpos[IFDOWN].x0))
		return (1);
	if (cub->player.tile->down->id == '1'
		&& check_player(cub->player.tile->down->pos,
			cub->player.tile->down->pos.x0, cub->player.ifpos[IFDOWN],
			cub->player.ifpos[IFDOWN].x0))
		return (1);
	if (cub->player.tile->downright->id == '1'
		&& check_player(cub->player.tile->downright->pos,
			cub->player.tile->downright->pos.x0, cub->player.ifpos[IFDOWN],
			cub->player.ifpos[IFDOWN].x0))
		return (1);
	return (0);
}

int	check_player_right(t_cub *cub)
{
	get_ifpos(cub);
	if (cub->player.tile->upright->id == '1'
		&& check_player(cub->player.tile->upright->pos,
			cub->player.tile->upright->pos.x0, cub->player.ifpos[IFRIGHT],
			cub->player.ifpos[IFRIGHT].x0))
		return (1);
	if (cub->player.tile->right->id == '1'
		&& check_player(cub->player.tile->right->pos,
			cub->player.tile->right->pos.x0, cub->player.ifpos[IFRIGHT],
			cub->player.ifpos[IFRIGHT].x0))
		return (1);
	if (cub->player.tile->downright->id == '1'
		&& check_player(cub->player.tile->downright->pos,
			cub->player.tile->downright->pos.x0, cub->player.ifpos[IFRIGHT],
			cub->player.ifpos[IFRIGHT].x0))
		return (1);
	return (0);
}

int	check_player_left(t_cub *cub)
{
	get_ifpos(cub);
	if ((cub->player.tile->upleft->id == '1')
		&& check_player(cub->player.tile->upleft->pos,
			cub->player.tile->upleft->pos.x0, cub->player.ifpos[IFLEFT],
			cub->player.ifpos[IFLEFT].x0))
		return (1);
	if (cub->player.tile->left->id == '1'
		&& check_player(cub->player.tile->left->pos,
			cub->player.tile->left->pos.x0, cub->player.ifpos[IFLEFT],
			cub->player.ifpos[IFLEFT].x0))
		return (1);
	if (cub->player.tile->downleft->id == '1'
		&& check_player(cub->player.tile->downleft->pos,
			cub->player.tile->downleft->pos.x0, cub->player.ifpos[IFLEFT],
			cub->player.ifpos[IFLEFT].x0))
		return (1);
	return (0);
}
