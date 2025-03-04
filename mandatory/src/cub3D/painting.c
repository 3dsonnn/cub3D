/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:34:36 by efinda            #+#    #+#             */
/*   Updated: 2025/03/04 13:29:41 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	paint_ceiling_and_floor(t_cub *cub, int j)
{
	int	i;

	i = -1;
	while (++i < cub->img.height)
	{
		if (i < cub->img.height / 2)
			my_mlx_pixel_put(&cub->img, j, i, cub->scene.ceiling);
		else
			my_mlx_pixel_put(&cub->img, j, i, cub->scene.floor);
	}
}

static void	paint_column(t_cub *cub, int i)
{
	int	y;
	int	index;
	int	offset_x;
	int	offset_y;
	int	offset_index;

	if (cub->rays[i].dir.y)
		offset_x = (int)cub->rays[i].ver.wall.y % TILE;
	else
		offset_x = (int)cub->rays[i].hor.wall.x % TILE;
	y = cub->rays[i].col.top;
	while (y < cub->rays[i].col.bot)
	{
		offset_y = (y + cub->rays[i].col.dist_from_top) * ((double)TILE
				/ cub->rays[i].col.height);
		index = (y * cub->img.line_len) + i;
		offset_index = offset_x + (offset_y
				* cub->rays[i].col.texture->img.line_len);
		cub->img.addr[index] = cub->rays[i].col.texture->img.addr[offset_index];
		y++;
	}
}

void	paint(t_cub *cub, int i)
{
	paint_ceiling_and_floor(cub, i);
	paint_column(cub, i);
}
