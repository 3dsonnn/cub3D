/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:22:29 by efinda            #+#    #+#             */
/*   Updated: 2025/02/10 11:28:10 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static  void    get_first_intersection(t_cub *cub, t_intersection *tmp, int i)
{
	tmp->crd.x = floor(cub->player.pos.x0 / TILE_SIZE) * TILE_SIZE;
    if (FACE_RIGHT(ray->angle))
        tmp->crd.x += TILE_SIZE;
    tmp->crd.y = cub->player.pos.y0 + ((tmp->crd.x - cub->player.pos.x0) * cub->rays[i].tan);
}

static  void    get_steps(t_cub *cub, t_intersection *tmp, int i)
{
    tmp->step.x = TILE_SIZE;
	if (FACE_LEFT(ray->angle))
		tmp->step.x *= -1;
	tmp->step.y = TILE_SIZE * cub->rays[i].tan;
	if ((FACE_UP(ray->angle) && tmp->step.y > 0)
        || (FACE_DOWN(ray->angle) && tmp->step.y < 0))
		tmp->step.y *= -1;
}

static  inline  void    get_distance(t_cub *cub, int i)
{
    if (cub->rays[i].ver.intersected)
        cub->rays[i].ver.dist = sqrt(pow((cub->rays[i].ver.wall.x - cub->player.pos.x0), 2) + pow((cub->rays[i].ver.wall.y - cub->player.pos.y0), 2));
    else
        cub->rays[i].ver.dist = -42;
}

void    check_vertical_intersection(t_cub *cub, int i)
{
    t_intersection  tmp;

    cub->rays[i].ver.intersected = 0;
    get_first_intersection(cub, &tmp, i);
    get_steps(cub, &tmp, i);
    if (FACE_LEFT(cub->rays[i].angle))
        tmp->crd.x -= 1;
    while (inside_map(cub, tmp->crd.x, tmp->crd.y))
    {
        if (is_wall(cub, tmp->crd.x, tmp->crd.y))
        {
            if (FACE_LEFT(cub->rays[i].angle))
                tmp->crd.x += 1;
            cub->rays[i].ver.wall.x = tmp->crd.x;
            cub->rays[i].ver.wall.y = tmp->crd.y;
            cub->rays[i].ver.intersected = 1;
            break ;
        }
        tmp->crd.x += tmp->step.x;
        tmp->crd.y += tmp->step.y;
    }
    get_distance(cub, i);
}
