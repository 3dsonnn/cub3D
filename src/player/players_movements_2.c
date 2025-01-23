/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players_movements_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:07:49 by efinda            #+#    #+#             */
/*   Updated: 2025/01/23 07:23:13 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

int	check_if_same_tile(t_plane tile, int tilex0, int x, int y)
{
	while (tile.y0 < tile.y)
	{
		tile.x0 = tilex0;
		while (tile.x0 < tile.x)
		{
			if (tile.x0 == x && tile.y0 == y)
				return (1);
			tile.x0++;
		}
		tile.y0++;
	}
	return (0);
}

int	check_player_up(t_cub *cub, t_plane new_pos, int i)
{
	t_tile	*neighbors[] = {cub->player.tile->up, cub->player.tile->upleft,
			cub->player.tile->upright, cub->player.tile->down,
			cub->player.tile->downleft, cub->player.tile->downright,
			cub->player.tile->left, cub->player.tile->right};

	new_pos.x0 += (int)round(cub->player.size.x * cub->player.dir.x);
	new_pos.y0 += (int)round(cub->player.size.y * cub->player.dir.y);
	if (check_if_same_tile(cub->player.tile->pos, cub->player.tile->pos.x0,
			new_pos.x0, new_pos.y0))
		return (0);
	while (++i < 8)
		if (neighbors[i] && neighbors[i]->id == '1'
			&& check_if_same_tile(neighbors[i]->pos, neighbors[i]->pos.x0,
				new_pos.x0, new_pos.y0))
			return (1);
	return (0);
}

int	check_player_down(t_cub *cub, t_plane new_pos, int i)
{
	t_tile	*neighbors[] = {cub->player.tile->up, cub->player.tile->upleft,
			cub->player.tile->upright, cub->player.tile->down,
			cub->player.tile->downleft, cub->player.tile->downright,
			cub->player.tile->left, cub->player.tile->right};

	new_pos.x0 -= (int)round(cub->player.size.x * cub->player.dir.x);
	new_pos.y0 -= (int)round(cub->player.size.y * cub->player.dir.y);
	if (check_if_same_tile(cub->player.tile->pos, cub->player.tile->pos.x0,
			new_pos.x0, new_pos.y0))
		return (0);
	while (++i < 8)
		if (neighbors[i] && neighbors[i]->id == '1'
			&& check_if_same_tile(neighbors[i]->pos, neighbors[i]->pos.x0,
				new_pos.x0, new_pos.y0))
			return (1);
	return (0);
}

int	check_player_right(t_cub *cub, t_plane new_pos, int i)
{
	t_tile	*neighbors[] = {cub->player.tile->up, cub->player.tile->upleft,
			cub->player.tile->upright, cub->player.tile->down,
			cub->player.tile->downleft, cub->player.tile->downright,
			cub->player.tile->left, cub->player.tile->right};

	new_pos.x0 -= (int)round(cub->player.size.x * cub->player.dir.x0);
	new_pos.y0 -= (int)round(cub->player.size.y * cub->player.dir.y0);
	if (check_if_same_tile(cub->player.tile->pos, cub->player.tile->pos.x0,
			new_pos.x0, new_pos.y0))
		return (0);
	while (++i < 8)
		if (neighbors[i] && neighbors[i]->id == '1'
			&& check_if_same_tile(neighbors[i]->pos, neighbors[i]->pos.x0,
				new_pos.x0, new_pos.y0))
			return (1);
	return (0);
}

int	check_player_left(t_cub *cub, t_plane new_pos, int i)
{
	t_tile	*neighbors[] = {cub->player.tile->up, cub->player.tile->upleft,
			cub->player.tile->upright, cub->player.tile->down,
			cub->player.tile->downleft, cub->player.tile->downright,
			cub->player.tile->left, cub->player.tile->right};

	new_pos.x0 += (int)round(cub->player.size.x * cub->player.dir.x0);
	new_pos.y0 += (int)round(cub->player.size.y * cub->player.dir.y0);
	if (check_if_same_tile(cub->player.tile->pos, cub->player.tile->pos.x0,
			new_pos.x0, new_pos.y0))
		return (0);
	while (++i < 8)
		if (neighbors[i] && neighbors[i]->id == '1'
			&& check_if_same_tile(neighbors[i]->pos, neighbors[i]->pos.x0,
				new_pos.x0, new_pos.y0))
			return (1);
	return (0);
}
