/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:24:28 by efinda            #+#    #+#             */
/*   Updated: 2025/04/26 21:17:57 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

inline bool	is_door(t_tile *tile)
{
	return (tile->left->id == 'd' || tile->left->id == 'D'
		|| tile->down->id == 'd' || tile->down->id == 'D'
		|| tile->right->id == 'd' || tile->right->id == 'D'
		|| tile->up->id == 'd' || tile->up->id == 'D');
}

static void	toggle_door(t_tile *tile)
{
	if (!tile)
		return ;
	if (tile->id == 'D')
		tile->id = 'd';
	else if (tile->id == 'd')
		tile->id = 'D';
}

void	open_or_close_door(t_tile *cur)
{
	toggle_door(cur->left);
	toggle_door(cur->right);
	toggle_door(cur->up);
	toggle_door(cur->down);
}
