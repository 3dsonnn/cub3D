/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rays_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 08:59:36 by efinda            #+#    #+#             */
/*   Updated: 2025/04/01 21:33:48 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

inline void    init_rays(t_cub *cub)
{
    cub->rays = (t_ray *)ft_calloc(cub->img.width, sizeof(t_ray));
    if (!cub->rays)
    {
        free_tiles(&cub->minimap.tiles, -1, cub->scene.map.size.y);
        my_mlx_error_free(cub, "Failed to allocate memory for rays");
    }
    cub->ppd = (cub->img.width / 2) / tan(FOV / 2);
}

static  void    choose_intersection(t_ray *ray)
{
    ray->dir = (t_point){0, 0};
    if (ray->hor.dist < ray->ver.dist)
    {
        ray->dist = ray->hor.dist;
        ray->wall = (t_dpoint){ray->hor.wall.x, ray->hor.wall.y};
        ray->dir.x = 1;
    }
    else
    {
        ray->dist = ray->ver.dist;
        ray->wall = (t_dpoint){ray->ver.wall.x, ray->ver.wall.y};
        ray->dir.y = 1;
    }
}

static  void    get_column(t_cub *cub, t_ray *ray)
{
    ray->dist *= cos(ft_normalizer(ray->angle - cub->player.angle));
    ray->height = (int)(TILE / ray->dist * cub->ppd);
    ray->top = ((cub->img.height - ray->height) / 2) + cub->player.updown;
    ray->bot = ((cub->img.height + ray->height) / 2) + cub->player.updown;
    if (ray->bot > cub->img.height)
        ray->bot = cub->img.height;
}

void    get_rays(t_cub *cub, int j)
{
    while (++j < cub->img.width)
    {
        cub->rays[j].angle = ft_normalizer(cub->player.angle + atan((j - cub->img.width / 2) / cub->ppd));
        cub->rays[j].tan = tan(cub->rays[j].angle);
        check_horizontal_intersection(cub, cub->rays + j);
        check_vertical_intersection(cub, cub->rays + j);
        choose_intersection(cub->rays + j);
        get_column(cub, cub->rays + j);
        get_texture_img(cub, cub->rays + j, cub->rays[j].angle, cub->rays[j].dir);
	    paint_column(cub, cub->rays + j, (t_point){j, -1}, (t_point){0, 0});
    }
}
