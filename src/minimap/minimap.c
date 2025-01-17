/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:20:53 by efinda            #+#    #+#             */
/*   Updated: 2025/01/17 14:36:36 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static	void	draw_player(t_cub *cub)
{
	int	x0;
	int	x;
	int	y0;
	int	y;

	y0 = cub->player.pos.y0;
	x = cub->player.pos.x;
	y = cub->player.pos.y;
	while (y0 < y)
	{
		x0 = cub->player.pos.x0;
		while (x0 < x)
		{
			my_mlx_pixel_put(&cub->minimap.img, x0, y0, 0xFFFF00);
			x0++;
		}
		y0++;
	}
}

static	void	paint_tile(t_cub *cub, t_tile tile)
{
	int	x0;
	int	x;
	int	y0;
	int	y;

	y0 = tile.pos.y0;
	x = tile.pos.x;
	y = tile.pos.y;
	while (y0 < y)
	{
		x0 = tile.pos.x0;
		while (x0 < x)
		{
			my_mlx_pixel_put(&cub->minimap.img, x0, y0, tile.color);
			x0++;
		}
		y0++;
	}
}

void	minimap(t_cub *cub, int i, int j)
{
	mlx_clear_window(cub->mlx, cub->win);
	refresh_minimap(cub, -1, -1);
	while (++i < cub->size.y)
	{
		j = -1;
		while (++j < cub->size.x)
		{
			paint_tile(cub, cub->minimap.tiles[i][j]);
		}
	}
	draw_player(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->minimap.img.img, 10, 10);
}
