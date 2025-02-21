/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rays.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 08:59:36 by efinda            #+#    #+#             */
/*   Updated: 2025/02/21 16:41:32 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

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
    cub->rays[i].col.dist = cub->rays[i].dist * cos(cub->rays[i].angle - cub->player.angle);
    cub->rays[i].col.height = (int)(TILE / cub->rays[i].col.dist * cub->ppd);
    cub->rays[i].col.top = (cub->img.height - cub->rays[i].col.height) / 2;
    if (cub->rays[i].col.top < 0)
        cub->rays[i].col.top = 0;
    cub->rays[i].col.bottom = (cub->img.height + cub->rays[i].col.height) / 2;
    if (cub->rays[i].col.bottom > cub->img.height)
        cub->rays[i].col.bottom = cub->img.height;
    cub->rays[i].col.dist_from_top = (cub->rays[i].col.height - cub->img.width) / 2;
    if (FACE_UP(cub->rays[i].angle) && cub->rays[i].dir.x && !cub->rays[i].dir.y)
        cub->rays[i].col.texture = &cub->scene.textures[NO];
    if (FACE_DOWN(cub->rays[i].angle) && cub->rays[i].dir.x && !cub->rays[i].dir.y)
        cub->rays[i].col.texture = &cub->scene.textures[SO];
    if (FACE_RIGHT(cub->rays[i].angle) && cub->rays[i].dir.y && !cub->rays[i].dir.x)
        cub->rays[i].col.texture = &cub->scene.textures[EA];
    if (FACE_LEFT(cub->rays[i].angle) && cub->rays[i].dir.y && !cub->rays[i].dir.x)
        cub->rays[i].col.texture = &cub->scene.textures[WE];
}

void    get_rays(t_cub *cub, int i)
{
    while (++i < cub->img.width)
    {
        cub->rays[i].angle = cub->player.angle + atan((i - cub->img.width / 2) / cub->ppd);
        cub->rays[i].angle = ft_normalizer(cub->rays[i].angle);
        cub->rays[i].tan = tan(cub->rays[i].angle);
        check_horizontal_intersection(cub, i);
        check_vertical_intersection(cub, i);
        choose_intersection(cub, i);
        get_column(cub, i);
    }
}
