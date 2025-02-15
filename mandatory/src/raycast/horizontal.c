/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:22:29 by efinda            #+#    #+#             */
/*   Updated: 2025/02/15 15:19:04 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static  void    get_first_intersection(t_cub *cub, t_intersection *tmp, int i)
{
	tmp->crd.y = floor(cub->player.pos.y / TILE) * TILE;
    if (FACE_DOWN(ray->angle))
        tmp->crd.y += TILE;
    tmp->crd.x = cub->player.pos.x + ((tmp->crd.y - cub->player.pos.y) / cub->rays[i].tan);
}

static  void    get_steps(t_cub *cub, t_intersection *tmp, int i)
{
	tmp->step.y = TILE;
	if (FACE_UP(ray->angle))
		tmp->step.y *= -1;
	tmp->step.x = TILE / cub->rays[i].tan;
	if ((FACE_LEFT(ray->angle) && tmp->step.x > 0)
        || (FACE_RIGHT(ray->angle) && tmp->step.x < 0))
		tmp->step.x *= -1;
}

static  inline  void    get_distance(t_cub *cub, int i)
{
    if (cub->rays[i].hor.intersected)
        cub->rays[i].hor.dist = sqrt(pow((cub->rays[i].hor.wall.x - cub->player.pos.x), 2) + pow((cub->rays[i].hor.wall.y - cub->player.pos.y), 2));
    else
        cub->rays[i].hor.dist = -42;
}

void    check_horizontal_intersection(t_cub *cub, int i)
{
    t_intersection  tmp;

    cub->rays[i].hor.intersected = 0;
    get_first_intersection(cub, &tmp, i);
    get_steps(cub, &tmp, i);
    if (FACE_UP(cub->rays[i].angle))
        tmp.crd.y -= 1;
    while (inside_map(cub, tmp.crd.x, tmp.crd.y))
    {
        if (is_wall(cub, tmp.crd.x, tmp.crd.y))
        {
            if (FACE_UP(cub->rays[i].angle))
                tmp.crd.y += 1;
            cub->rays[i].hor.wall.x = tmp.crd.x;
            cub->rays[i].hor.wall.y = tmp.crd.y;
            cub->rays[i].hor.intersected = 1;
            break ;
        }
        tmp.crd.x += tmp.step.x;
        tmp.crd.y += tmp.step.y;
    }
    get_distance(cub, i);
}
