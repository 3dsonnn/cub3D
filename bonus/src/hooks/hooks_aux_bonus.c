/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_aux_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 19:10:28 by efinda            #+#    #+#             */
/*   Updated: 2025/04/25 19:58:39 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

inline void	alt_space(t_cub *cub, int keycode)
{
	if (keycode == ALT)
	{
		if (cub->hooks.alt)
		{
			cub->hooks.alt = 0;
			mlx_mouse_hide(cub->mlx, cub->win);
		}
		else
		{
			cub->hooks.alt = 1;
			mlx_mouse_show(cub->mlx, cub->win);
		}
		return ;
	}
	if (cub->hooks.space)
	{
		cub->hooks.space = 0;
		mlx_do_key_autorepeatoff(cub->mlx);
	}
	else
	{
		cub->hooks.space = 1;
		mlx_do_key_autorepeaton(cub->mlx);
	}
}

void	open_door(t_cub *cub, t_tile *cur)
{
	cub->scene.map.door.cur_time = get_current_time();
	if (cur->left->id == 'D')
		cur->left->id = 'd';
	if (cur->right->id == 'D')
		cur->right->id = 'd';
	if (cur->up->id == 'D')
		cur->up->id = 'd';
	if (cur->down->id == 'D')
		cur->down->id = 'd';
}
