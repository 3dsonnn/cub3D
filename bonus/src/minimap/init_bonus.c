/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 18:30:45 by efinda            #+#    #+#             */
/*   Updated: 2025/04/26 19:34:15 by efinda           ###   ########.fr       */
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

void	init_minimap(t_cub *cub)
{
	my_mlx_new_img(cub->mlx, &cub->minimap.img,
		(t_point){MINI_TILE * 11, MINI_TILE * 11});
	if (!cub->minimap.img.img)
		my_mlx_error_free(cub, "Failed to create the minimap image");
	my_mlx_get_data_addr(&cub->minimap.img);
	if (!cub->minimap.img.addr)
		my_mlx_error_free(cub,
			"Failed to get the address of the minimap image");
	init_tiles(cub, &cub->minimap.tiles, -1, -1);
	link_tiles(cub, 0, 0);
	set_tiles(cub, -1, -1);
	ft_mtxfree(&cub->scene.map.content);
}
