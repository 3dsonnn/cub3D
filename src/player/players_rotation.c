/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players_rotation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 08:08:47 by efinda            #+#    #+#             */
/*   Updated: 2025/01/23 06:43:56 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	get_angle(t_cub *cub, int flag)
{
	if (flag == -1)
		return ;
	if (flag)
		cub->player.angle = fmod(cub->player.angle - 15.0 + 360.0, 360.0);
	else
		cub->player.angle = fmod(cub->player.angle + 15.0, 360.0);
}

void	rotate_player(t_cub *cub, int flag)
{
	double	threshold;

	cub->flag = 1;
	threshold = 1e-6;
	get_angle(cub, flag);
	cub->player.dir.x = cos(cub->player.angle * (M_PI / 180.0));
	cub->player.dir.y = -sin(cub->player.angle * (M_PI / 180.0));
	if (fabs(cub->player.dir.x) < threshold)
		cub->player.dir.x = 0;
	if (fabs(cub->player.dir.y) < threshold)
		cub->player.dir.y = 0;
	cub->player.dir.x0 = -sin(cub->player.angle * (M_PI / 180.0));
	cub->player.dir.y0 = -cos(cub->player.angle * (M_PI / 180.0));
	if (fabs(cub->player.dir.x0) < threshold)
		cub->player.dir.x0 = 0;
	if (fabs(cub->player.dir.y0) < threshold)
		cub->player.dir.y0 = 0;
	cub->player.fov.x = fmod(cub->player.angle - (FOV / 2) + 360.0, 360.0);
	cub->player.fov.y = fmod(cub->player.angle + (FOV / 2), 360.0);
}
