/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:30:45 by efinda            #+#    #+#             */
/*   Updated: 2025/03/31 17:18:22 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static void	is_obx(t_cub *cub, int max)
{
	if (cub->scene.map.size.x < 11 && cub->scene.map.size.y < 11)
	{
		if (cub->scene.map.size.x > cub->scene.map.size.y)
			max = cub->scene.map.size.x;
		else
			max = cub->scene.map.size.y;
		cub->minimap.tilesize = (int)floor(220 / max);
		cub->minimap.box = 0;
	}
	else
	{
		cub->minimap.tilesize = 20;
		cub->minimap.box = 1;
	}
}

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

void	init_minimap(t_cub *cub)
{
	is_obx(cub, 0);
	init_tiles(cub, &cub->minimap.tiles, -1, -1);
	link_tiles(cub, 0, 0);
	set_tiles(cub, -1, -1);
	ft_mtxfree(&cub->scene.map.content);
}
