/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:30:45 by efinda            #+#    #+#             */
/*   Updated: 2025/05/05 09:42:35 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static void	init_tiles(t_cub *cub, t_tile ***tiles, int i, int j)
{
	*tiles = (t_tile **)malloc(sizeof(t_tile *) * (cub->scene.map.size.y));
	if (!(*tiles))
		my_mlx_error_free(cub,
			"Failed to allocate memory for the minimap tiles");
	while (++i < cub->scene.map.size.y)
	{
		j = -1;
		(*tiles)[i] = (t_tile *)malloc(sizeof(t_tile) * cub->scene.map.size.x);
		if (!(*tiles)[i])
		{
			while (--i >= 0)
				free((*tiles)[i]);
			free(*tiles);
			my_mlx_error_free(cub,
				"Failed to allocate memory for the minimap tiles");
		}
		while (++j < cub->scene.map.size.x)
		{
			(*tiles)[i][j].up = NULL;
			(*tiles)[i][j].down = NULL;
			(*tiles)[i][j].left = NULL;
			(*tiles)[i][j].right = NULL;
		}
	}
}

void	init_minimap_aux_imgs(t_cub *cub, t_mmap *mmap)
{
	int	aux;

	my_mlx_duplicate_img(cub->mlx, &mmap->circle, mmap->img);
	if (!mmap->circle.img)
		my_mlx_error_free(cub, "Failed to create the minimap circle image");
	if (!mmap->circle.addr)
		my_mlx_error_free(cub,
			"Failed to get the address of the minimap circle image");
	aux = (int)ceil(sqrt(2 * (mmap->circle.width * mmap->circle.width)));
	my_mlx_new_img(cub->mlx, &mmap->rotated, (t_point){aux, aux});
	if (!mmap->rotated.img)
		my_mlx_error_free(cub, "Failed to create the minimap rotated image");
	my_mlx_get_data_addr(&mmap->rotated);
	if (!mmap->rotated.addr)
		my_mlx_error_free(cub,
			"Failed to get the address of the minimap rotated image");
	my_mlx_duplicate_img(cub->mlx, &mmap->padded, mmap->rotated);
	if (!mmap->padded.img)
		my_mlx_error_free(cub, "Failed to create the minimap padded image");
	if (!mmap->padded.addr)
		my_mlx_error_free(cub,
			"Failed to get the address of the minimap padded image");
}

void	init_minimap(t_cub *cub)
{
	my_mlx_new_img(cub->mlx, &cub->minimap.img, (t_point){MINI_TILE * 11,
		MINI_TILE * 11});
	if (!cub->minimap.img.img)
		my_mlx_error_free(cub, "Failed to create the minimap image");
	my_mlx_get_data_addr(&cub->minimap.img);
	if (!cub->minimap.img.addr)
		my_mlx_error_free(cub,
			"Failed to get the address of the minimap image");
	init_minimap_aux_imgs(cub, &cub->minimap);
	init_tiles(cub, &cub->minimap.tiles, -1, -1);
	link_tiles(cub, 0, 0);
	set_tiles(cub, -1, -1);
	ft_mtxfree(&cub->scene.map.content);
}
