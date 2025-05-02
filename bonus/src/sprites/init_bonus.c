/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 09:50:57 by efinda            #+#    #+#             */
/*   Updated: 2025/05/02 07:53:59 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static int	get_clear_img(t_cub *cub, t_img *img)
{
	my_mlx_new_img(cub->mlx, img, (t_point){GUN_WIDTH, GUN_HEIGHT});
	if (!img->img)
	{
		get_explicit_error_message(&cub->scene,
			(t_strs){"Failed to create the clear image", NULL, NULL, NULL, NULL,
			NULL});
		return (1);
	}
	my_mlx_get_data_addr(img);
	if (!img->addr)
	{
		get_explicit_error_message(&cub->scene,
			(t_strs){"Failed to get the address of the clear image", NULL, NULL,
			NULL, NULL, NULL});
		return (1);
	}
	return (0);
}

static int	sprite_xpm_file_to_img(t_cub *cub, t_img *img, char *path)
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
	my_mlx_get_data_addr(img);
	if (!img->addr)
	{
		get_explicit_error_message(&cub->scene,
			(t_strs){"Failed to get the address of image from ", path, ".\n",
			"Make sure the configuration files were not modified", NULL, NULL});
		return (1);
	}
	return (0);
}

void	get_sprites_images(t_cub *cub, int i)
{
	const char	*paths[24] = {CROSSHAIR_PATH, IDLE_PATH, PUTTING_01_PATH,
		PUTTING_02_PATH, PUTTING_03_PATH, RECHARGING_01_PATH,
		RECHARGING_02_PATH, RECHARGING_03_PATH, RECHARGING_04_PATH,
		RECHARGING_05_PATH, RECHARGING_06_PATH, RECHARGING_IDLE_PATH,
		SHELL_01_PATH, SHELL_02_PATH, SHELL_03_PATH, SHELL_04_PATH,
		SHELL_05_PATH, SHELL_06_PATH, SHELL_07_PATH, SHELL_08_PATH,
		SHELL_09_PATH, SHOOTING_01_PATH, SHOOTING_02_PATH,
		SHOOTING_IDLE_PATH};

	while (++i < 24)
	{
		if (sprite_xpm_file_to_img(cub, &cub->sprites.imgs[i],
				(char *)paths[i]))
			my_mlx_error_free(cub, cub->scene.tmp);
		if (i)
			my_mlx_resize_img(cub->mlx, &cub->sprites.imgs[i],
				(t_point){GUN_WIDTH, GUN_HEIGHT});
	}
	my_mlx_resize_img(cub->mlx, &cub->sprites.imgs[CROSSHAIR],
		(t_point){CROSSHAIR_SIZE, CROSSHAIR_SIZE});
	if (get_clear_img(cub, &cub->sprites.imgs[CLEAR]))
		my_mlx_error_free(cub, cub->scene.tmp);
}
