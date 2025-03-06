/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:34:36 by efinda            #+#    #+#             */
/*   Updated: 2025/03/06 07:07:30 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	paint(t_cub *cub, int i, int j, t_point pixel)
{
	if (cub->rays[j].dir.y)
		pixel.x = (int)cub->rays[j].ver.wall.y % TILE;
	else
		pixel.x = (int)cub->rays[j].hor.wall.x % TILE;
	while (++i < cub->rays[j].col.top)
		my_mlx_pixel_put(&cub->img, j, i, cub->scene.ceiling);
	while (i < cub->rays[j].col.bot)
	{
		pixel.y = (i + cub->rays[j].col.dist_from_top) * ((double)TILE
				/ cub->rays[j].col.height);
		my_mlx_pixel_put(&cub->img, j, i,
			my_mlx_get_pixel(&cub->rays[j].texture->img, pixel.x, pixel.y));
		i++;
	}
	while (i < cub->img.height)
	{
		my_mlx_pixel_put(&cub->img, j, i, cub->scene.floor);
		i++;
	}
}
