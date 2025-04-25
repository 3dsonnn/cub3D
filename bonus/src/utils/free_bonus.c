/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:47:58 by efinda            #+#    #+#             */
/*   Updated: 2025/04/25 20:07:22 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

void	free_tiles(t_tile ***tiles, int i, int size)
{
	if (!tiles || !*tiles || !(*tiles)[0])
		return ;
	while (++i < size)
		if ((*tiles)[i])
			free((*tiles)[i]);
	free(*tiles);
	*tiles = NULL;
}

void	destroy_all_imgs(t_cub *cub)
{
	int	i;

	i = -1;
	my_mlx_destroy_img(cub->mlx, &cub->img);
	my_mlx_destroy_img(cub->mlx, &cub->scene.map.door.door);
	my_mlx_destroy_img(cub->mlx, &cub->scene.map.door.key);
	while (++i < 4)
		my_mlx_destroy_img(cub->mlx, &cub->scene.textures[i].img);
	my_mlx_destroy_img(cub->mlx, &cub->minimap.img);
	i = -1;
	while (++i < 27)
		my_mlx_destroy_img(cub->mlx, &cub->sprites.imgs[i]);
}
