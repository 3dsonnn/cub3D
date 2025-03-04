/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 08:08:47 by efinda            #+#    #+#             */
/*   Updated: 2025/03/04 17:31:42 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static void	get_angle(t_cub *cub, int flag)
{
	if (flag == -1)
		return ;
	if (flag)
	{
		cub->player.angle = cub->player.angle - DEG_TO_RAD(15.0);
		cub->player.angle = ft_normalizer(cub->player.angle);
	}
	else
	{
		cub->player.angle = cub->player.angle + DEG_TO_RAD(15.0);
		cub->player.angle = ft_normalizer(cub->player.angle);
	}
}

void	rotate_player(t_cub *cub, int flag)
{
	double	threshold;

	threshold = 1e-6;
	get_angle(cub, flag);
	cub->player.dir.x = cos(cub->player.angle);
	cub->player.dir.y = -sin(cub->player.angle);
	if (fabs(cub->player.dir.x) < threshold)
		cub->player.dir.x = 0;
	if (fabs(cub->player.dir.y) < threshold)
		cub->player.dir.y = 0;
	cub->player.dir.x0 = cub->player.dir.y;
	cub->player.dir.y0 = -cub->player.dir.x;
}
