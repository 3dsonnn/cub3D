/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:40:46 by efinda            #+#    #+#             */
/*   Updated: 2025/03/04 17:30:45 by efinda           ###   ########.fr       */
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

static void	my_mlx_xpm_file_to_image(t_cub *cub, int i)
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
				&cub->scene.textures[i].img.bpp, &cub->scene.textures[i].img.line_len,
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

void	init_mlx(t_cub *cub, int i)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		exit_error("Failed to initialize mlx", &cub->scene);
	my_mlx_xpm_file_to_image(cub, -1);
	mlx_get_screen_size(cub->mlx, &cub->img.width, &cub->img.height);
	cub->win = mlx_new_window(cub->mlx, cub->img.width, cub->img.height, "cub3D");
	if (!cub->win)
		my_mlx_free(cub, "Failed to create the window", (t_plane){-1, 4, 1, 1});
	cub->img.img = mlx_new_image(cub->mlx, cub->img.width, cub->img.height);
	if (!cub->img.img)
		my_mlx_free(cub, "Failed to create the main image", (t_plane){-1, 4, 1, 1});
	cub->img.addr = (int *)mlx_get_data_addr(cub->img.img, &cub->img.bpp,
			&cub->img.line_len, &cub->img.endian);
	if (!cub->img.addr)
	{
		mlx_destroy_image(cub->mlx, cub->img.img);
		my_mlx_free(cub, "Failed to get the address of the main image", (t_plane){-1, 4, 1, 1});
	}
	cub->img.line_len /= 4;
}
