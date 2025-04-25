/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:40:46 by efinda            #+#    #+#             */
/*   Updated: 2025/04/24 10:43:56 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	my_mlx_free(t_cub *cub, char *message, t_plane flag)
{
	while (++(flag.x0) < (flag.x))
		my_mlx_destroy_img(cub->mlx, &cub->scene.textures[flag.x0].img);
	if (flag.y0)
	{
		mlx_destroy_window(cub->mlx, cub->win);
		cub->win = NULL;
	}
	if (flag.y)
	{
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
		cub->mlx = NULL;
	}
	exit_error(message, &cub->scene);
}

static void	convert_textures_to_imgs(t_cub *cub, t_texture textures[4], int i)
{
	while (++i < 4)
	{
		textures[i].img.img = mlx_xpm_file_to_image(cub->mlx, textures[i].path,
				&textures[i].img.width, &textures[i].img.height);
		if (!textures[i].img.img)
		{
			cub->scene.tmp = ft_strjoin("Failed to load image from ",
					textures[i].path, 0);
			my_mlx_free(cub, cub->scene.tmp, (t_plane){-1, (i - 1), 0, 1});
		}
		my_mlx_get_data_addr(&textures[i].img);
		if (!textures[i].img.addr)
		{
			cub->scene.tmp = ft_strjoin("Failed to get the address",
					"of image from ", 0);
			cub->scene.tmp = ft_strjoin(cub->scene.tmp, textures[i].path, 1);
			my_mlx_free(cub, cub->scene.tmp, (t_plane){-1, (i + 1), 0, 1});
		}
		ft_strfree(&textures[i].path);
	}
}

void	init_mlx(t_cub *cub, int i)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		exit_error("Failed to initialize mlx", &cub->scene);
	convert_textures_to_imgs(cub, cub->scene.textures, -1);
	cub->win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "cub3D");
	if (!cub->win)
		my_mlx_free(cub, "Failed to create the window", (t_plane){-1, 4, 1, 1});
	my_mlx_new_img(cub->mlx, &cub->img, (t_point){WIDTH, HEIGHT});
	if (!cub->img.img)
		my_mlx_free(cub, "Failed to create the main image", (t_plane){-1, 4, 1,
			1});
	my_mlx_get_data_addr(&cub->img);
	if (!cub->img.addr)
	{
		my_mlx_destroy_img(cub->mlx, &cub->img);
		my_mlx_free(cub, "Failed to get the address of the main image",
			(t_plane){-1, 4, 1, 1});
	}
}

void	init_dfl(t_cub *cub, int i)
{
	cub->mlx = NULL;
	cub->win = NULL;
	my_mlx_init_img(&cub->img);
	cub->scene = (t_scene){.fd = 0, .floor = 0, .ceiling = 0, .mtx = NULL,
		.tmp = NULL, .line = NULL, .line_cpy = NULL, .elements = NULL,
		.line_nbr = (t_nbr){.value = 0, .str = NULL}};
	cub->scene.map = (t_map){.head = NULL, .crds = NULL, .content = NULL,
		.start = '\0', .spos = (t_point){0, 0}, .size = (t_point){0, 0}};
	while (++i < 4)
	{
		cub->scene.textures[i].path = NULL;
		my_mlx_init_img(&cub->scene.textures[i].img);
	}
	cub->player = (t_player){.angle = 0.0, .pos = (t_dpoint){0.0, 0.0},
		.dir = (t_dpoint){0.0, 0.0}, .plane = (t_dpoint){0.0, 0.0}};
	cub->rays = NULL;
	cub->ppd = 0.0;
}

void	init_rays(t_cub *cub)
{
	cub->rays = (t_ray *)ft_calloc(cub->img.width, sizeof(t_ray));
	if (!cub->rays)
		my_mlx_free(cub, "Failed to allocate memory for rays", (t_plane){-1, 4,
			1, 1});
	cub->ppd = (cub->img.width / 2) / tan(FOV / 2);
}
