/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus_aux.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 19:10:28 by efinda            #+#    #+#             */
/*   Updated: 2025/03/16 19:22:41 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

inline	void	alt(t_cub *cub)
{
	if (cub->alt)
	{
		cub->alt = 0;
		mlx_mouse_hide(cub->mlx, cub->win);
	}
	else
	{
		cub->alt = 1;
		mlx_mouse_show(cub->mlx, cub->win);
	}
}
