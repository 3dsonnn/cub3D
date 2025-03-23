/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_images.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 23:28:02 by efinda            #+#    #+#             */
/*   Updated: 2025/03/23 10:38:19 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static char	*get_path_aux(int key)
{
	if (key == 11)
		return (RECHARGING_IDLE_PATH);
	if (key == 12)
		return (SHELL_01_PATH);
	if (key == 13)
		return (SHELL_02_PATH);
	if (key == 14)
		return (SHELL_03_PATH);
	if (key == 15)
		return (SHELL_04_PATH);
	if (key == 16)
		return (SHELL_05_PATH);
	if (key == 17)
		return (SHOOTING_01_PATH);
	if (key == 18)
		return (SHOOTING_02_PATH);
	if (key == 19)
		return (SHOOTING_IDLE_PATH);
	return (NULL);
}

static char	*get_path(int key)
{
	if (!key)
		return (CROSSHAIR_PATH);
	if (key == 1)
		return (IDLE_PATH);
	if (key == 2)
		return (PUTTING_01_PATH);
	if (key == 3)
		return (PUTTING_02_PATH);
	if (key == 4)
		return (PUTTING_03_PATH);
	if (key == 5)
		return (RECHARGING_01_PATH);
	if (key == 6)
		return (RECHARGING_02_PATH);
	if (key == 7)
		return (RECHARGING_03_PATH);
	if (key == 8)
		return (RECHARGING_04_PATH);
	if (key == 9)
		return (RECHARGING_05_PATH);
	if (key == 10)
		return (RECHARGING_06_PATH);
	return (get_path_aux(key));
}

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
	*img = my_mlx_resize_img(cub->mlx, *img, (t_point){16, 16});
	return (0);
}

void	check_player_images(t_cub *cub, int i)
{
	while (++i < 20)
	{
		if (my_mlx_xpm_file_to_image(cub, &cub->player.imgs[i], get_path(i)))
		{
			while (--i >= 0)
				mlx_destroy_image(cub->mlx, cub->player.imgs[i].img);
			my_mlx_free(cub, cub->scene.tmp, (t_plane){-1, 4, 0, 1});
		}
	}
}
