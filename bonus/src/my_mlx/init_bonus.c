/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcsilv <marcsilv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:40:46 by efinda            #+#    #+#             */
/*   Updated: 2025/04/23 09:16:59 by marcsilv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

void	my_mlx_free(t_cub *cub, char *message, t_plane flag)
{
	while (++(flag.x0) < (flag.x))
		mlx_destroy_image(cub->mlx, cub->scene.textures[flag.x0].img.img);
	if (flag.y0)
		mlx_destroy_window(cub->mlx, cub->win);
	if (flag.y)
	{
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
	}
	exit_error(message, &cub->scene);
}

static void	get_textures_images(t_cub *cub, int i)
{
	while (++i < 4)
	{
		cub->scene.textures[i].img.img = mlx_xpm_file_to_image(cub->mlx,
				cub->scene.textures[i].path, &cub->scene.textures[i].img.width,
				&cub->scene.textures[i].img.height);
		if (!cub->scene.textures[i].img.img)
		{
			cub->scene.tmp = ft_strjoin("Failed to load image from ",
					cub->scene.textures[i].path);
			my_mlx_free(cub, cub->scene.tmp, (t_plane){-1, (i - 1), 0, 1});
		}
		cub->scene.textures[i].img.addr = (int *)mlx_get_data_addr(cub->scene.textures[i].img.img,
				&cub->scene.textures[i].img.bpp,
				&cub->scene.textures[i].img.line_len,
				&cub->scene.textures[i].img.endian);
		if (!cub->scene.textures[i].img.addr)
		{
			cub->scene.tmp = ft_strjoin("Failed to get the address of image from ",
					cub->scene.textures[i].path);
			my_mlx_free(cub, cub->scene.tmp, (t_plane){-1, (i + 1), 0, 1});
		}
		cub->scene.textures[i].img.line_len /= 4;
		ft_strfree(&cub->scene.textures[i].path);
	}
}

static	void	my_mlx_new_image(t_cub *cub)
{
	cub->img.img = mlx_new_image(cub->mlx, cub->img.width, cub->img.height);
	if (!cub->img.img)
		my_mlx_free(cub, "Failed to create the main image", (t_plane){-1, 4, 1,
			1});
	cub->img.addr = (int *)mlx_get_data_addr(cub->img.img, &cub->img.bpp,
			&cub->img.line_len, &cub->img.endian);
	if (!cub->img.addr)
	{
		mlx_destroy_image(cub->mlx, cub->img.img);
		my_mlx_free(cub, "Failed to get the address of the main image",
			(t_plane){-1, 4, 1, 1});
	}
	cub->img.line_len /= 4;
}

void	init_mlx(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		exit_error("Failed to initialize mlx", &cub->scene);
	get_textures_images(cub, -1);
	check_player_images(cub, -1);
	cub->img.width = WIDTH;
	cub->img.height = HEIGHT;
	cub->win = mlx_new_window(cub->mlx, cub->img.width, cub->img.height,
			"cub3D");
	if (!cub->win)
		my_mlx_free(cub, "Failed to create the window", (t_plane){-1, 4, 1, 1});
	my_mlx_new_image(cub);
	mlx_mouse_hide(cub->mlx, cub->win);
	cub->scene.door.img.img = mlx_xpm_file_to_image(cub->mlx, DOOR, &cub->scene.door.img.width, &cub->scene.door.img.height);
	cub->scene.door.img.addr = (int *)mlx_get_data_addr(cub->scene.door.img.img, &cub->scene.door.img.bpp, &cub->scene.door.img.line_len, &cub->scene.door.img.endian);
	cub->scene.door.img.line_len /= 4;
	cub->scene.door.img = my_mlx_resize_img(cub->mlx, cub->scene.door.img, (t_point){64, 64});

	cub->scene.e_key.img.img = mlx_xpm_file_to_image(cub->mlx, E_TEXTURE, &cub->scene.e_key.img.width, &cub->scene.e_key.img.height);
	cub->scene.e_key.img.addr = (int *)mlx_get_data_addr(cub->scene.e_key.img.img, &cub->scene.e_key.img.bpp, &cub->scene.e_key.img.line_len, &cub->scene.e_key.img.endian);
	cub->scene.e_key.img.line_len /= 4;
	cub->scene.e_key.img = my_mlx_resize_img(cub->mlx, cub->scene.e_key.img, (t_point){32, 32});
	mlx_mouse_move(cub->mlx, cub->win, (int)(cub->img.width / 2), (int)(cub->img.height / 2));
}
