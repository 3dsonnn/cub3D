/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:20:38 by efinda            #+#    #+#             */
/*   Updated: 2025/03/14 19:47:16 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

void draw_filtered_img(t_cub *cub, int cross_x, int cross_y, t_img *img)
{
	int x, y;
	int pixel;
	int color;
	
	for (y = 0; y < img->height; y++) {
		for (x = 0; x < img->width; x++) {
			pixel = (y * img->line_len) + (x * (img->bpp / 8));
			color = my_mlx_get_pixel(img, x, y);
			
			if (color == 0xFFFFFF) // Only draw white pixels
				my_mlx_pixel_put(&cub->img, cross_x + x, cross_y + y, color);
		}
	}
}

void	draw_crosshair(void *mlx, void *win, t_cub *cub)
{
	t_img	crosshair;

	crosshair.width = 32;
	crosshair.height = 32;

	crosshair.img = mlx_xpm_file_to_image(cub->mlx, "./animated_sprites/crosshair2.xpm", &crosshair.width, &crosshair.height);

	crosshair.addr = (int *)mlx_get_data_addr(crosshair.img, &crosshair.bpp, &crosshair.line_len, &crosshair.endian);
	crosshair.line_len /= 4;
	draw_filtered_img(cub, cub->img.width / 2 - 16, cub->img.height / 2 - 16, &crosshair);

}

void	draw_shotgun(t_cub *cub)
{
	t_img	shotgun;

	int i = 0; int j = 0;

	shotgun.img = mlx_xpm_file_to_image(cub->mlx, "./animated_sprites/shotgun/idle.xpm", &shotgun.width, &shotgun.height);
	shotgun.addr = (int *)mlx_get_data_addr(shotgun.img, &shotgun.bpp, &shotgun.line_len, &shotgun.endian);
	shotgun.line_len /= 4;
	int x = cub->img.width / 2;
	int y = cub->img.height - shotgun.height;
	while (++y < cub->img.height)
	{
		x = cub->img.width / 2;
		j = 0;
		while (++x < shotgun.width + cub->img.width / 2)
		{
		int color = my_mlx_get_pixel(&shotgun, j, i);
			if (color == 0xFF000000)
				continue;
			my_mlx_pixel_put(&cub->img, j, i, color);
			j++;
		}
		i++;
	}
}

void	cub3D(t_cub *cub)
{
	//player(cub);
	get_rays(cub, -1);
	minimap(cub);
	draw_health_bar(cub->mlx, cub->win, cub->player.health, cub);
	draw_crosshair(cub->mlx, cub->win, cub);
	draw_shotgun(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
}
