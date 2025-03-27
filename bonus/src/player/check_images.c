/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_images.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcsilv <marcsilv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 23:28:02 by efinda            #+#    #+#             */
/*   Updated: 2025/03/27 14:24:24 by marcsilv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static char	*get_path_aux(int key)
{
	if (key == 11)
		return (RECHARGING_IDLE_PATH);
	if (key == 12)
		return (SHOOTING_01_PATH);
	if (key == 13)
		return (SHOOTING_02_PATH);
	if (key == 14)
		return (SHELL_01_PATH);
	if (key == 15)
		return (SHELL_02_PATH);
	if (key == 16)
		return (SHELL_03_PATH);
	if (key == 17)
		return (SHELL_04_PATH);
	if (key == 18)
		return (SHELL_05_PATH);
	if (key == 19)
		return (SHELL_06_PATH);
	if (key == 20)
		return (SHELL_07_PATH);
	if (key == 21)
		return (SHELL_08_PATH);
	if (key == 22)
		return (SHELL_09_PATH);
	if (key == 23)
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
	return (0);
}

void	check_player_images(t_cub *cub, int i)
{
	const char	*paths[24] = {CROSSHAIR_PATH, IDLE_PATH, PUTTING_01_PATH,
			PUTTING_02_PATH, PUTTING_03_PATH, RECHARGING_01_PATH,
			RECHARGING_02_PATH, RECHARGING_03_PATH, RECHARGING_04_PATH,
			RECHARGING_05_PATH, RECHARGING_06_PATH, RECHARGING_IDLE_PATH,
			SHOOTING_01_PATH, SHOOTING_02_PATH, SHELL_01_PATH, SHELL_02_PATH,
			SHELL_03_PATH, SHELL_04_PATH, SHELL_05_PATH, SHELL_06_PATH,
			SHELL_07_PATH, SHELL_08_PATH, SHELL_09_PATH, SHOOTING_IDLE_PATH};

	while (++i < 24)
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
					cub->player.imgs[i], (t_point){512, 490});
	}
	cub->player.imgs[i].img = mlx_new_image(cub->mlx, 512, 490);
	cub->player.imgs[i].width = 512;
	cub->player.imgs[i].height = 490;
	cub->player.imgs[i].addr = (int *)mlx_get_data_addr(cub->player.imgs[i].img,
			&cub->player.imgs[i].bpp, &cub->player.imgs[i].line_len,
			&cub->player.imgs[i].endian);
	cub->player.imgs[i].line_len /= 4;
}
