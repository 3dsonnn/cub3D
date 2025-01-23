/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players_movements_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 01:25:12 by efinda            #+#    #+#             */
/*   Updated: 2025/01/23 07:11:11 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static int	check_surrounding_tiles(t_cub *cub)
{
	if (cub->player.tile->up->id == '1'
		|| cub->player.tile->upleft->id == '1'
		|| cub->player.tile->upright->id == '1'
		|| cub->player.tile->down->id == '1'
		|| cub->player.tile->downleft->id == '1'
		|| cub->player.tile->downright->id == '1'
		|| cub->player.tile->right->id == '1'
		|| cub->player.tile->left->id == '1')
		return (0);
	return (1);
}

int	check_players_newpos_overlap(t_cub *cub, t_plane flag)
{
	t_plane	new_pos;

	new_pos = cub->player.pos;
	if (check_surrounding_tiles(cub))
		return (0);
	if (flag.x0)
		if (check_player_up(cub, new_pos, -1))
			return (1);
	else if (flag.x)
		if (check_player_down(cub, new_pos, -1))
			return (1);
	else if (flag.y0)
		if (check_player_right(cub, new_pos, -1))
			return (1);
	else if (flag.y)
		if (check_player_left(cub, new_pos, -1))
			return (1);
	return (0);
}
