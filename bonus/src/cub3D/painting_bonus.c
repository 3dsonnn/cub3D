/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:34:36 by efinda            #+#    #+#             */
/*   Updated: 2025/03/13 09:18:35 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

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
		pixel.y = (cub->rays[j].texture->img.height * (i
					- cub->rays[j].col.top)) / cub->rays[j].col.height;
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

void draw_rect(void *mlx, void *win, int x, int y, int width, int height, int color, t_cub *cub)
{
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
			my_mlx_pixel_put(&cub->img, x + j, y + i, color);
        }
    }
}

void draw_health_bar(void *mlx, void *win, int health, t_cub *cub) 
{
    int bar_width = 400;
    int bar_height = 40;
    int x = 20;
    int y = 900;

    int current_width = (bar_width * health) / 100;

    draw_rect(mlx, win, x, y, bar_width, bar_height, 0x333333, cub);
    draw_rect(mlx, win, x, y, current_width, bar_height, 0xFF0000, cub);
}
