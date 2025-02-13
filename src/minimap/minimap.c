/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:20:53 by efinda            #+#    #+#             */
/*   Updated: 2025/02/10 14:30:16 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	draw_mini_player(t_cub *cub)
{
	int		radius;
	t_plane	crd;

	radius = 5;
	while (--radius >= 0)
		bresenham_circle(cub, cub->player.pos.x0, cub->player.pos.y0, radius);
	cub->player.pos.x = cub->player.pos.x0 + ((cub->player.size * 2)
			* cos(cub->player.angle * (M_PI / 180.0)));
	cub->player.pos.y = cub->player.pos.y0 - ((cub->player.size * 2)
			* sin(cub->player.angle * (M_PI / 180.0)));
	crd.x0 = (int)cub->player.pos.x0;
	crd.x = (int)cub->player.pos.x;
	crd.y = (int)cub->player.pos.y0;
	crd.y0 = (int)cub->player.pos.y;
	bresenham_line(cub, crd, (t_point){0, 0}, (t_point){0, 0});
}

void	minimap(t_cub *cub, int i, int j)
{
	if (cub->minimap.box)
		paint_box(cub, cub->minimap.corners[TOPLEFT]);
	else
		paint(cub, -1, -1);
	draw_mini_player(cub);
}
