/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players_movements_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 01:25:12 by efinda            #+#    #+#             */
/*   Updated: 2025/01/20 02:55:15 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

int	check_players_newpos_overlap(t_cub *cub, t_plane flag)
{
	if (flag.x0)
		if (check_player_up(cub))
			return (1);
	else if (flag.x)
		if (check_player_down(cub))
			return (1);
	else if (flag.y0)
		if (check_player_right(cub))
			return (1);
	else if (flag.y)
		if (check_player_left(cub))
			return (1);
	return (0);
}
