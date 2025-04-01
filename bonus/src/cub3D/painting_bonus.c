/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painting_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:34:36 by efinda            #+#    #+#             */
/*   Updated: 2025/04/01 21:03:17 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

void	paint_column(t_cub *cub, t_ray *ray, t_point iter, t_point pixel)
{
	if (ray->dir.y)
		pixel.x = (int)ray->ver.wall.y % TILE;
	else
		pixel.x = (int)ray->hor.wall.x % TILE;
	while (++iter.y < ray->top)
		my_mlx_pixel_put(&cub->img, iter.x, iter.y, cub->scene.ceiling);
	while (iter.y < ray->bot)
	{
		pixel.y = ft_map(iter.y - ray->top, (int[]){0, ray->height}, (int[]){0,
				ray->img.height});
		my_mlx_pixel_put(&cub->img, iter.x, iter.y, my_mlx_get_pixel(ray->img,
				pixel.x, pixel.y));
		iter.y++;
	}
	while (iter.y < cub->img.height)
	{
		my_mlx_pixel_put(&cub->img, iter.x, iter.y, cub->scene.floor);
		iter.y++;
	}
}
