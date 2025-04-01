/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 22:22:36 by efinda            #+#    #+#             */
/*   Updated: 2025/04/01 19:56:47 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static void	rotate_sideways(t_cub *cub, int keycode)
{
	double	angle_delta;

	if (keycode == RIGHT)
		angle_delta = ROT;
	else
		angle_delta = -ROT;
	cub->player.angle += angle_delta;
	cub->player.angle = ft_normalizer(cub->player.angle);
	cub->player.dir.x = cos(cub->player.angle);
	cub->player.dir.y = sin(cub->player.angle);
	cub->player.plane.x = -cub->player.dir.y;
	cub->player.plane.y = cub->player.dir.x;
}

int	rotate_player(t_cub *cub, int keycode)
{
	if (keycode == RIGHT || keycode == LEFT)
	{
		rotate_sideways(cub, keycode);
		return (0);
	}
	else if ((keycode == UP && (cub->player.updown + 10) > 600)
		|| (keycode == DOWN && (cub->player.updown - 10) < -600))
		return (1);
	if (keycode == UP)
		cub->player.updown += 10;
	if (keycode == DOWN)
		cub->player.updown -= 10;
	return (0);
}
