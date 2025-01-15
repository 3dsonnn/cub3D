/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:40:46 by efinda            #+#    #+#             */
/*   Updated: 2025/01/15 02:01:18 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	my_mlx_xpm_file_to_image(t_cub *cub, int i, int j)
{
	while (++i < 4)
	{
		cub->scene.walls[i].img.img = mlx_xpm_file_to_image(cub->mlx,
				cub->scene.walls[i].path, &cub->scene.walls[i].width,
				&cub->scene.walls[i].height);
		if (!cub->scene.walls[i].img.img)
		{
			j = i;
			while (--i >= 0)
				mlx_destroy_image(cub->mlx, cub->scene.walls[i].img.img);
			mlx_destroy_display(cub->mlx);
			free(cub->mlx);
			cub->scene.tmp = ft_strjoin("Failed to load the image from ",
					cub->scene.walls[j].path);
			exit_error(cub->scene.tmp, &cub->scene);
		}
		cub->scene.walls[i].img.addr = mlx_get_data_addr(cub->scene.walls[i].img.img,
				&cub->scene.walls[i].img.bpp, &cub->scene.walls[i].img.line_len,
				&cub->scene.walls[i].img.endian);
		ft_strfree(&cub->scene.walls[i].path);
	}
}

static void	paint_floor_and_ceiling(t_cub *cub, int x, int y)
{
	int	fc[2];

	fc[0] = mlx_get_color_value(cub->mlx,
			mlx_get_rgb_color(cub->scene.fc[0].rgb[0], cub->scene.fc[0].rgb[1],
				cub->scene.fc[0].rgb[2]));
	fc[1] = mlx_get_color_value(cub->mlx,
			mlx_get_rgb_color(cub->scene.fc[1].rgb[0], cub->scene.fc[1].rgb[1],
				cub->scene.fc[1].rgb[2]));
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			if (y < HEIGHT / 2)
				my_mlx_pixel_put(&cub->img, x, y, fc[0]);
			else
				my_mlx_pixel_put(&cub->img, x, y, fc[1]);
		}
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
}

void	my_mlx_init(t_cub *cub)
{
	cub->mlx = mlx_init();
	my_mlx_xpm_file_to_image(cub, -1, 0);
	cub->win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "cub3D");
	cub->img.img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bpp,
			&cub->img.line_len, &cub->img.endian);
	paint_floor_and_ceiling(cub, -1, -1);
	// mlx_put_image_to_window(cub->mlx, cub->win, cub->scene.walls->img.img, 0,
	// 	0);
	// mlx_put_image_to_window(cub->mlx, cub->win, cub->scene.walls[1].img.img,
	// 	cub->scene.walls->width, 0);
	// mlx_put_image_to_window(cub->mlx, cub->win, cub->scene.walls[2].img.img,
	// 	cub->scene.walls[0].width + cub->scene.walls[1].width, 0);
	// mlx_put_image_to_window(cub->mlx, cub->win, cub->scene.walls[3].img.img,
	// 	cub->scene.walls[0].width + cub->scene.walls[1].width
	// 	+ cub->scene.walls[2].width, 0);
}