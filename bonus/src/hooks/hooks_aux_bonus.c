/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_aux_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 19:10:28 by efinda            #+#    #+#             */
/*   Updated: 2025/03/24 23:24:37 by efinda           ###   ########.fr       */
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
