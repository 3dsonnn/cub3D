/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_images_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 23:28:02 by efinda            #+#    #+#             */
/*   Updated: 2025/03/24 17:06:40 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static int	my_mlx_xpm_file_to_image(t_cub *cub, t_img *img, char *path)
{
	if (!path)
		return (1);
	img->img = mlx_xpm_file_to_image(cub->mlx, path, &img->width, &img->height);
	if (!img->img)
	{
		get_explicit_error_message(&cub->scene,
			(t_strs){"Failed to load image from ", path, "\n",
			"Make sure the configuration files were not modified", NULL, NULL});
		return (1);
	}
	img->addr = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
	if (!img->addr)
	{
		mlx_destroy_image(cub->mlx, img->img);
		get_explicit_error_message(&cub->scene,
			(t_strs){"Failed to get the address of image from ", path, ".\n",
			"Make sure the configuration files were not modified", NULL, NULL});
		return (1);
	}
	img->line_len /= 4;
	return (0);
}

void	check_player_images(t_cub *cub, int i)
{
	const char	*paths[20] = {CROSSHAIR_PATH, IDLE_PATH, PUTTING_01_PATH,
		PUTTING_02_PATH, PUTTING_03_PATH, RECHARGING_01_PATH,
		RECHARGING_02_PATH, RECHARGING_03_PATH, RECHARGING_04_PATH,
		RECHARGING_05_PATH, RECHARGING_06_PATH, RECHARGING_IDLE_PATH,
		SHOOTING_01_PATH, SHOOTING_02_PATH, SHELL_01_PATH, SHELL_02_PATH,
		SHELL_03_PATH, SHELL_04_PATH, SHELL_05_PATH, SHOOTING_IDLE_PATH};

	while (++i < 20)
	{
		if (my_mlx_xpm_file_to_image(cub, &cub->player.imgs[i],
				(char *)paths[i]))
		{
			while (--i >= 0)
				mlx_destroy_image(cub->mlx, cub->player.imgs[i].img);
			my_mlx_free(cub, cub->scene.tmp, (t_plane){-1, 4, 0, 1});
		}
		if (!i)
			cub->player.imgs[i] = my_mlx_resize_img(cub->mlx,
					cub->player.imgs[i], (t_point){16, 16});
		else
			cub->player.imgs[i] = my_mlx_resize_img(cub->mlx,
					cub->player.imgs[i], (t_point){640, 640});
	}
}
