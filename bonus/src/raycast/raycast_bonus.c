/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 08:59:36 by efinda            #+#    #+#             */
/*   Updated: 2025/04/29 11:19:48 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static void	choose_intersection(t_cub *cub, t_ray *ray)
{
	if (ray->hor.dist < ray->ver.dist)
	{
		ray->dist = ray->hor.dist;
		ray->wall = (t_dpoint){.x = ray->hor.wall.x, .y = ray->hor.wall.y};
		ray->dir = (t_point){.x = 1, .y = 0};
		ray->ver.is_door = 0;
	}
	else
	{
		ray->dist = ray->ver.dist;
		ray->wall = (t_dpoint){.x = ray->ver.wall.x, .y = ray->ver.wall.y};
		ray->dir = (t_point){.x = 0, .y = 1};
		ray->hor.is_door = 0;
	}
	if (!ray->dist)
		(ray->dist)++;
}

static void	get_column(t_cub *cub, t_ray *ray)
{
	ray->dist *= cos(ft_normalizer(ray->angle - cub->player.angle));
	ray->height = (int)(TILE / ray->dist * cub->ppd);
	ray->top = ((int)(cub->img.height - ray->height) / 2) + cub->player.updown;
	ray->bot = ((int)(cub->img.height + ray->height) / 2) + cub->player.updown;
	if (ray->bot > cub->img.height)
		ray->bot = cub->img.height;
}

void	get_rays(t_cub *cub, int j)
{
	paint_ceiling_and_floor(cub, (t_point){j, j});
	while (++j < cub->img.width)
	{
		cub->rays[j].hor.is_door = 0;
		cub->rays[j].ver.is_door = 0;
		cub->rays[j].angle = ft_normalizer(cub->player.angle + atan((j
						- cub->img.width / 2) / cub->ppd));
		cub->rays[j].tan = tan(cub->rays[j].angle);
		check_horizontal_intersection(cub, cub->rays + j, 0);
		check_vertical_intersection(cub, cub->rays + j, 0);
		choose_intersection(cub, cub->rays + j);
		get_column(cub, cub->rays + j);
		get_texture(cub, cub->rays + j, cub->rays[j].angle, cub->rays[j].dir);
		paint_wall(cub, cub->rays + j, (t_point){j, cub->rays[j].top - 1},
			(t_point){0, 0});
	}
}
