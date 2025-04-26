/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:20:38 by efinda            #+#    #+#             */
/*   Updated: 2025/04/26 20:15:42 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

void	cub3D(t_cub *cub)
{
	get_rays(cub, -1);
	minimap(cub);
	player(cub);
	if (is_door(cub->minimap.cur))
		my_mlx_put_img_to_img(&cub->img, cub->scene.map.door.key,
			(t_point){(cub->img.width / 2) - (cub->scene.map.door.key.width / 2),
			(cub->img.height / 2) + (cub->img.height / 3)}, 1);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->minimap.img.img, 10, 10);
	mlx_put_image_to_window(cub->mlx, cub->win,
		cub->sprites.imgs[HEALTH_BAR].img, 20, HEIGHT - 20
		- cub->sprites.imgs[HEALTH_BAR].height);
}
