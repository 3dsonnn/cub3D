/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:20:38 by efinda            #+#    #+#             */
/*   Updated: 2025/04/17 10:10:25 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	paint_column(t_cub *cub, t_ray *ray, t_point iter, t_point pixel)
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

static void	choose_intersection(t_cub *cub, t_ray *ray)
{
	if (ray->hor.dist < ray->ver.dist)
	{
		ray->dist = ray->hor.dist;
		ray->wall = (t_dpoint){.x = ray->hor.wall.x, .y = ray->hor.wall.y};
		ray->dir = (t_point){.x = 1, .y = 0};
	}
	else
	{
		ray->dist = ray->ver.dist;
		ray->wall = (t_dpoint){.x = ray->ver.wall.x, .y = ray->ver.wall.y};
		ray->dir = (t_point){.x = 0, .y = 1};
	}
	if (!ray->dist)
		(ray->dist)++;
}

static void	get_column(t_cub *cub, t_ray *ray)
{
	ray->dist = ray->dist
		* cos(ft_normalizer(ray->angle - cub->player.angle));
	ray->height = (int)(TILE / ray->dist * cub->ppd);
	ray->top = (int)(cub->img.height - ray->height) / 2;
	ray->bot = (int)(cub->img.height + ray->height) / 2;
	if (ray->bot > cub->img.height)
		ray->bot = cub->img.height;
}

void	raycast(t_cub *cub, int j)
{
	while (++j < cub->img.width)
	{
		cub->rays[j].angle = ft_normalizer(cub->player.angle + atan((j - cub->img.width / 2) / cub->ppd));
		cub->rays[j].tan = tan(cub->rays[j].angle);
		check_horizontal_intersection(cub, cub->rays + j);
		check_vertical_intersection(cub, cub->rays + j);
		choose_intersection(cub, cub->rays + j);
		get_column(cub, cub->rays + j);
		get_texture(cub, cub->rays + j, cub->rays[j].angle,
				cub->rays[j].dir);
		paint_column(cub, cub->rays + j, (t_point){j, -1}, (t_point){0, 0});
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
}
