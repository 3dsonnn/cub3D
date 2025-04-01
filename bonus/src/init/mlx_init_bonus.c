/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:40:46 by efinda            #+#    #+#             */
/*   Updated: 2025/04/01 21:16:48 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static void	get_textures_images(t_cub *cub, t_texture textures[4], int i)
{
	while (++i < 4)
	{
		textures[i].img.img = mlx_xpm_file_to_image(cub->mlx, textures[i].path,
				&textures[i].img.width, &textures[i].img.height);
		if (!textures[i].img.img)
		{
			cub->scene.tmp = ft_strjoin("Failed to load image from ",
					textures[i].path);
			my_mlx_error_free(cub, cub->scene.tmp);
		}
		my_mlx_get_data_addr(&textures[i].img);
		if (!textures[i].img.addr)
		{
			cub->scene.tmp = ft_strjoin("Failed to get the address of image from ",
					textures[i].path);
			my_mlx_error_free(cub, cub->scene.tmp);
		}
		ft_strfree(&textures[i].path);
	}
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
