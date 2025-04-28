/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcsilv <marcsilv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:20:38 by efinda            #+#    #+#             */
/*   Updated: 2025/04/26 14:29:15 by marcsilv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

void	cub3D(t_cub *cub)
{
	get_rays(cub, -1);
	minimap(cub);
	player(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
	// mlx_put_image_to_window(cub->mlx, cub->win, cut.img, 510, 510);
	// mlx_put_image_to_window(cub->mlx, cub->win, cub->minimap.img.img, 10, 10);

	mlx_put_image_to_window(cub->mlx, cub->win,
		cub->sprites.imgs[HEALTH_BAR].img, 20, HEIGHT - 20
		- cub->sprites.imgs[HEALTH_BAR].height);
}
