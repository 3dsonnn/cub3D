/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_aux_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 19:10:28 by efinda            #+#    #+#             */
/*   Updated: 2025/05/02 04:34:28 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

int	my_mlx_mouse_click(int keycode, int x, int y, t_cub *cub)
{
	(void)x;
	(void)y;
	if (keycode == 1 && cub->sprites.idle)
	{
		cub->sprites.idle = false;
		cub->sprites.shooting = true;
		cub->sprites.cur_frame_index = SHOOTING_01;
		cub->sprites.last_frame_time = get_current_time();
	}
	return (0);
}

inline void	alt_space(t_cub *cub, int keycode)
{
	if (keycode == ALT)
	{
		if (cub->hooks.alt)
			mlx_mouse_hide(cub->mlx, cub->win);
		else
			mlx_mouse_show(cub->mlx, cub->win);
		cub->hooks.alt = !cub->hooks.alt;
	}
	else
	{
		if (cub->hooks.space)
			mlx_do_key_autorepeatoff(cub->mlx);
		else
			mlx_do_key_autorepeaton(cub->mlx);
		cub->hooks.space = !cub->hooks.space;
	}
}
