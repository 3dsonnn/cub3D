/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 10:32:10 by efinda            #+#    #+#             */
/*   Updated: 2025/04/30 18:12:41 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static int	smoother_lerp_color(int colors[2], float range[2], float pos)
{
	float	step;

	if (!(range[1] - range[0]))
		step = 0.0f;
	else
		step = ft_clamp((pos - range[0]) / (range[1] - range[0]), 0.0f, 1.0f);
	step = ft_clamp(step, 0.0f, 1.0f);
	step = step * step * step * (step * (step * 6.0f - 15.0f) + 10.0f);
	return (my_mlx_get_transparent_color(colors[0], colors[1], step));
}

void	paint_ceiling_and_floor(t_cub *cub, t_point iter)
{
	int	up;

	up = HALF_HEIGHT + cub->player.updown;
	while (++iter.y < cub->img.height)
	{
		iter.x = -1;
		while (++iter.x < cub->img.width)
		{
			if (iter.y < up)
				my_mlx_pixel_put(&cub->img, iter.x, iter.y,
					smoother_lerp_color((int []){cub->scene.ceiling, FOG_COLOR},
						(float []){0, up}, iter.y));
			else
				my_mlx_pixel_put(&cub->img, iter.x, iter.y,
					smoother_lerp_color((int []){cub->scene.floor, FOG_COLOR},
						(float []){cub->img.height, up}, iter.y));
		}
	}
}

void	paint_wall(t_cub *cub, t_ray *ray, t_point iter, t_point pixel)
{
	float	fog_strength;
	int		color;

	if (ray->dir.y)
		pixel.x = (int)ray->ver.wall.y % TILE;
	else
		pixel.x = (int)ray->hor.wall.x % TILE;
	while (++iter.y < ray->bot)
	{
		fog_strength = pow(ft_clamp((ray->dist / FOG_MAX_DIST), 0, 1), 2);
		color = my_mlx_get_transparent_color(my_mlx_get_pixel(ray->img, pixel.x,
					pixel.y), FOG_COLOR, fog_strength);
		pixel.y = ft_map(iter.y - ray->top, (int []){0, ray->height},
				(int []){0, ray->img.height});
		my_mlx_pixel_put(&cub->img, iter.x, iter.y, color);
	}
}
