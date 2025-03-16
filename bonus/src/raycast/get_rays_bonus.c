/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rays_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 08:59:36 by efinda            #+#    #+#             */
/*   Updated: 2025/03/16 08:44:35 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

inline void    init_rays(t_cub *cub)
{
    cub->rays = (t_ray *)ft_calloc(cub->img.width, sizeof(t_ray));
    if (!cub->rays)
        my_mlx_free(cub, "Failed to allocate memory for rays", (t_plane){-1, 4, 1, 1});
    cub->ppd = (cub->img.width / 2) / tan(FOV / 2);
}

static  void    choose_intersection(t_cub *cub, int i)
{
    cub->rays[i].dir.x = 0;
    cub->rays[i].dir.y = 0;
    if (cub->rays[i].hor.dist < cub->rays[i].ver.dist)
    {
        cub->rays[i].dist = cub->rays[i].hor.dist;
        cub->rays[i].wall.x = cub->rays[i].hor.wall.x;
        cub->rays[i].wall.y = cub->rays[i].hor.wall.y;
        cub->rays[i].dir.x = 1;
    }
    else
    {
        cub->rays[i].dist = cub->rays[i].ver.dist;
        cub->rays[i].wall.x = cub->rays[i].ver.wall.x;
        cub->rays[i].wall.y = cub->rays[i].ver.wall.y;
        cub->rays[i].dir.y = 1;
    }
    if (!cub->rays[i].dist)
        (cub->rays[i].dist)++;
}

static  void    get_column(t_cub *cub, int i)
{
    cub->rays[i].col.dist = cub->rays[i].dist * cos(ft_normalizer(cub->rays[i].angle - cub->player.angle));
    cub->rays[i].col.height = (int)(TILE / cub->rays[i].col.dist * cub->ppd);
    cub->rays[i].col.top = (cub->img.height - cub->rays[i].col.height) / 2;
    // if (cub->rays[i].col.top < 0)
    //     cub->rays[i].col.top = 0;
    cub->rays[i].col.bot = (cub->img.height + cub->rays[i].col.height) / 2;
    if (cub->rays[i].col.bot > cub->img.height)
        cub->rays[i].col.bot = cub->img.height;
}

void    get_rays(t_cub *cub, int j)
{
    while (++j < cub->img.width)
    {
        cub->rays[j].angle = cub->player.angle + atan((j - cub->img.width / 2) / cub->ppd);
        cub->rays[j].angle = ft_normalizer(cub->rays[j].angle);
        cub->rays[j].tan = tan(cub->rays[j].angle);
        check_horizontal_intersection(cub, j);
        check_vertical_intersection(cub, j);
        choose_intersection(cub, j);
        get_column(cub, j);
        cub->rays[j].texture = get_texture(cub, cub->rays[j].angle, cub->rays[j].dir);
	    paint(cub, -1, j, (t_point){0, 0});
    }
}
