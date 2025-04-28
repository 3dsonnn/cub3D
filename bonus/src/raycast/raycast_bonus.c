/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcsilv <marcsilv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 08:59:36 by efinda            #+#    #+#             */
/*   Updated: 2025/04/28 18:37:49 by marcsilv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

float	clamp(float value, float min, float max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

float	smootherstep(float t)
{
	t = clamp(t, 0.0f, 1.0f);
	return t * t * t * (t * (t * 6.0f - 15.0f) + 10.0f);
}

int	smoother_lerp_color(int color1, int color2, float from, float to, float pos)
{
	float	t;

	if (to - from == 0)
		t = 0.0f;
	else
		t = clamp((pos - from) / (to - from), 0.0f, 1.0f);
	t = smootherstep(t);
	int r1 = (color1 >> 16) & 0xFF;
	int g1 = (color1 >> 8) & 0xFF;
	int b1 = color1 & 0xFF;
	int r2 = (color2 >> 16) & 0xFF;
	int g2 = (color2 >> 8) & 0xFF;
	int b2 = color2 & 0xFF;
	int r = (int)(r1 * (1 - t) + r2 * t);
	int g = (int)(g1 * (1 - t) + g2 * t);
	int b = (int)(b1 * (1 - t) + b2 * t);
	return (r << 16) | (g << 8) | b;
}

static void	paint_column(t_cub *cub, t_ray *ray, t_point iter, t_point pixel)
{
	float	fog_strength;
	int	final_color;
	int	color;
	if (ray->dir.y)
		pixel.x = (int)ray->ver.wall.y % TILE;
	else
		pixel.x = (int)ray->hor.wall.x % TILE;
	while (iter.y < ray->bot)
	{
		fog_strength = pow(clamp((ray->dist / FOG_MAX_DISTANCE), 0 , 1), 1.5);
		color = my_mlx_get_pixel(ray->img, pixel.x, pixel.y);
		final_color = my_mlx_get_transparent_color(color, FOG_COLOR, fog_strength);
		pixel.y = ft_map(iter.y - ray->top, (int []){0, ray->height},
				(int []){0, ray->img.height});
		my_mlx_pixel_put(&cub->img, iter.x, iter.y, final_color);
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
	ray->dist *= cos(ft_normalizer(ray->angle - cub->player.angle));
	ray->height = (int)(TILE / ray->dist * cub->ppd);
	ray->top = (int)(cub->img.height - ray->height) / 2;
	ray->bot = (int)(cub->img.height + ray->height) / 2;
	if (ray->bot > cub->img.height)
		ray->bot = cub->img.height;
}

int lerp_color(int color, float from, float to, float pos)
{
	float	t;
	int	r1, g1, b1;
	int	r2, g2, b2;

	if (to - from == 0)
		t = 0.0f;
	else
		t = clamp((pos - from) / (to - from), 0.0f, 1.0f);
	r1 = (color >> 16) & 0xFF;
	g1 = (color >> 8) & 0xFF;
	b1 = (color) & 0xFF;
	r2 = (FOG_COLOR >> 16) & 0xFF;
	g2 = (FOG_COLOR >> 8) & 0xFF;
	b2 = (FOG_COLOR) & 0xFF;
	int r = (int)(r1 * (1 - t) + r2 * t);
	int g = (int)(g1 * (1 - t) + g2 * t);
	int b = (int)(b1 * (1 - t) + b2 * t);
	return (r << 16) | (g << 8) | b;
}

void	get_rays(t_cub *cub, int j)
{
	while (++j < cub->img.height)
	{
		int k =-1;
		while (++k < cub->img.width)
		{
			if (j < cub->img.height / 2)
				my_mlx_pixel_put(&cub->img, k, j,
						smoother_lerp_color(cub->scene.ceiling, FOG_COLOR, 0, cub->img.height / 2, j));
			else
				my_mlx_pixel_put(&cub->img, k, j,
						smoother_lerp_color(cub->scene.floor, FOG_COLOR, cub->img.height, cub->img.height / 2,  j));
		}
	}
	j = -1;
	while (++j < cub->img.width)
	{
		cub->rays[j].angle = ft_normalizer(cub->player.angle + atan((j
			- cub->img.width / 2) / cub->ppd));
		cub->rays[j].tan = tan(cub->rays[j].angle);
		check_horizontal_intersection(cub, cub->rays + j);
		check_vertical_intersection(cub, cub->rays + j);
		choose_intersection(cub, cub->rays + j);
		get_column(cub, cub->rays + j);
		get_texture(cub, cub->rays + j, cub->rays[j].angle, cub->rays[j].dir);
		paint_column(cub, cub->rays + j, (t_point){j, cub->rays[j].top}, (t_point){0, 0});
	}
}
