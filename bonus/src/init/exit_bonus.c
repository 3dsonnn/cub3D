/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:37:04 by efinda            #+#    #+#             */
/*   Updated: 2025/05/06 16:59:19 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static void	free_scene(t_scene *scene, void *mlx)
{
	int	i;

	i = -1;
	ft_mtxfree(&scene->mtx);
	ft_strfree(&scene->tmp);
	ft_strfree(&scene->line);
	ft_strfree(&scene->line_cpy);
	ft_strfree(&scene->elements);
	ft_strfree(&scene->line_nbr.str);
	free_rows(&scene->map.head);
	free_map_crds(&scene->map.crds);
	ft_mtxfree(&scene->map.content);
	my_mlx_destroy_img(mlx, &scene->map.door.key);
	my_mlx_destroy_img(mlx, &scene->map.door.door);
	while (++i < 4)
	{
		ft_strfree(&scene->textures[i].path);
		my_mlx_destroy_img(mlx, &scene->textures[i].img);
	}
    scene->cub = NULL;
}

static void	free_mlx(t_cub *cub)
{
	if (cub->rays)
	{
		free(cub->rays);
		cub->rays = NULL;
	}
	my_mlx_destroy_img(cub->mlx, &cub->img);
	if (cub->mlx)
	{
		if (cub->win)
		{
			mlx_destroy_window(cub->mlx, cub->win);
			cub->win = NULL;
		}
		mlx_do_key_autorepeaton(cub->mlx);
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
		cub->mlx = NULL;
	}
}

static void	free_minimap_and_sprites(t_cub *cub)
{
    int i;

    i = -1;
	my_mlx_destroy_img(cub->mlx, &cub->minimap.img);
	my_mlx_destroy_img(cub->mlx, &cub->minimap.circle);
	my_mlx_destroy_img(cub->mlx, &cub->minimap.rotated);
	my_mlx_destroy_img(cub->mlx, &cub->minimap.padded);
	free_tiles(&cub->minimap.tiles, -1, cub->scene.map.size.y);
	while (++i < 25)
		my_mlx_destroy_img(cub->mlx, &cub->sprites.imgs[i]);
}

static void	exit_error(t_nbr error)
{
	if (error.str)
	{
		error.value = write(2, "Error\n", 6);
		error.value = write(2, error.str, ft_strlen(error.str));
		error.value = write(2, "\n", 1);
		ft_strfree(&error.str);
		exit(1);
	}
}

void	exit_cub(t_cub *cub, char *message)
{
	t_nbr	error;

	error = (t_nbr){.value = 0, .str = ft_strdup(message)};
	free_scene(&cub->scene, cub->mlx);
	free_minimap_and_sprites(cub);
	free_mlx(cub);
    exit_error(error);
	exit(0);
}
