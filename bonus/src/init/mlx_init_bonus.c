/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:40:46 by efinda            #+#    #+#             */
/*   Updated: 2025/05/01 17:04:36 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static void	get_door_img(t_cub *cub, t_img *img, char *id, char *path)
{
	img->img = mlx_xpm_file_to_image(cub->mlx, path, &img->width, &img->height);
	if (!img->img)
	{
		get_explicit_error_message(&cub->scene, (t_strs){"Failed to load the",
			id, "image from ", path, "\n",
			"Make sure the configuration files were not modified"});
		my_mlx_error_free(cub, cub->scene.tmp);
	}
	my_mlx_get_data_addr(img);
	if (!img->addr)
	{
		get_explicit_error_message(&cub->scene,
			(t_strs){"Failed to get the address of the", id, "image from ",
			path, "\n", "Make sure the configuration files were not modified"});
		my_mlx_error_free(cub, cub->scene.tmp);
	}
	if (ft_strlen(id) == 6)
		my_mlx_resize_img(cub->mlx, img, (t_point){64, 64});
	else
		my_mlx_resize_img(cub->mlx, img, (t_point){32, 32});
}

static void	get_textures_images(t_cub *cub, t_texture textures[5], int i)
{
	while (++i < 4)
	{
		textures[i].img.img = mlx_xpm_file_to_image(cub->mlx, textures[i].path,
				&textures[i].img.width, &textures[i].img.height);
		if (!textures[i].img.img)
		{
			cub->scene.tmp = ft_strjoin("Failed to load image from ",
					textures[i].path, 2);
			my_mlx_error_free(cub, cub->scene.tmp);
		}
		my_mlx_get_data_addr(&textures[i].img);
		if (!textures[i].img.addr)
		{
			cub->scene.tmp = ft_strjoin(
					"Failed to get the address of image from ",
					textures[i].path, 2);
			my_mlx_error_free(cub, cub->scene.tmp);
		}
		ft_strfree(&textures[i].path);
	}
	get_door_img(cub, &cub->scene.map.door.door, " door ", DOOR_PATH);
	get_door_img(cub, &cub->scene.map.door.key, " door key ", E_KEY_PATH);
}

void	init_mlx(t_cub *cub)
{
	if (!XInitThreads())
		exit_error("Failed to initialize X11 threads", &cub->scene);
	cub->mlx = mlx_init();
	if (!cub->mlx)
		exit_error("Failed to initialize mlx", &cub->scene);
	get_textures_images(cub, cub->scene.textures, -1);
	get_sprites_images(cub, -1);
	cub->win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "cub3D");
	if (!cub->win)
		my_mlx_error_free(cub, "Failed to create the window");
	my_mlx_new_img(cub->mlx, &cub->img, (t_point){WIDTH, HEIGHT});
	if (!cub->img.img)
		my_mlx_error_free(cub, "Failed to create the main image");
	my_mlx_get_data_addr(&cub->img);
	if (!cub->img.addr)
		my_mlx_error_free(cub, "Failed to get the address of the main image");
	mlx_mouse_hide(cub->mlx, cub->win);
	mlx_mouse_move(cub->mlx, cub->win, (int)(cub->img.width / 2),
		(int)(cub->img.height / 2));
}
