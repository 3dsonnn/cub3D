/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 08:59:36 by efinda            #+#    #+#             */
/*   Updated: 2025/01/23 10:41:31 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static int	is_wall(double x, double y)
{
}

static int	is_within_map(double x, double y)
{
}

static void	check_horizontal_intersection(t_cub *cub, t_ray *ray)
{
	if (ray->face.y)
		ray->hor.y = floor(cub->player.pos.y0 / cub->minimap.tileheight)
			* cub->minimap.tileheight + cub->minimap.tileheight;
	else
		ray->hor.y = floor(cub->player.pos.y0 / cub->minimap.tileheight)
			* cub->minimap.tileheight - 1;
	ray->step.x = cub->minimap.tileheight / ray->tan;
	if (ray->face.y)
		ray->step.y = cub->minimap.tileheight;
	else
		ray->step.y = -cub->minimap.tileheight;
	ray->hor.x = cub->player.pos.x0 + (ray->hor.y - cub->player.pos.y0) / ray->tan;
	while (is_within_map(ray->hor.x, ray->hor.y) && !is_wall(ray->hor.x, ray->hor.y))
	{
		ray->hor.x += ray->step.x;
		ray->hor.y += ray->step.y;
	}
}

static void	check_vertical_intersection(t_cub *cub, t_ray *ray)
{
    if (ray->face.x)
		ray->vert.x = floor(cub->player.pos.x0 / cub->minimap.tilewidth)
			* cub->minimap.tilewidth + cub->minimap.tilewidth;
	else
		ray->hor.y = floor(cub->player.pos.x0 / cub->minimap.tilewidth)
			* cub->minimap.tilewidth - 1;
	ray->step.y = ray->tan * cub->minimap.tilewidth;
	if (ray->face.x)
		ray->step.x = cub->minimap.tilewidth;
	else
		ray->step.x = -cub->minimap.tilewidth;
	ray->vert.y = cub->player.pos.y0 + (ray->vert.x - cub->player.pos.x0) * ray->tan;
	while (is_within_map(ray->vert.x, ray->vert.y) && !is_wall(ray->vert.x, ray->vert.y))
	{
		ray->vert.x += ray->step.x;
		ray->vert.y += ray->step.y;
	}
}

void	cast_rays(t_cub *cub, int i)
{
	t_ray	ray;

	while (++i < MINIWIDTH)
	{
		ray.angle = cub->player.fov.x + i * cub->player.ray_step;
		ray.angle = fmod(ray.angle + 360.0, 360.0);
		ray.tan = tan(ray.angle);
		ray.face.x = (ray.angle < M_PI_2 || ray.angle > 3 * M_PI_2);
		ray.face.y = (ray.angle > 0 && ray.angle < M_PI);
		check_horizontal_intersection(cub, &ray);
		check_vertical_intersection(cub, &ray);
	}
}
