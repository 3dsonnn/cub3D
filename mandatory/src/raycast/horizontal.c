/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:22:29 by efinda            #+#    #+#             */
/*   Updated: 2025/04/23 19:06:21 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	get_first_intersection(t_cub *cub, t_intersection *tmp, t_ray *ray)
{
	tmp->crd.y = floor(cub->player.pos.y / TILE) * TILE;
	if (face_down(ray->angle))
		tmp->crd.y += TILE;
	tmp->crd.x = cub->player.pos.x + ((tmp->crd.y - cub->player.pos.y)
			/ ray->tan);
}

static void	get_steps(t_cub *cub, t_intersection *tmp, t_ray *ray)
{
	tmp->step.y = TILE;
	if (!face_down(ray->angle))
		tmp->step.y *= -1;
	tmp->step.x = TILE / ray->tan;
	if ((!face_right(ray->angle) && tmp->step.x > 0) || (face_right(ray->angle)
			&& tmp->step.x < 0))
		tmp->step.x *= -1;
}

static inline void	get_distance(t_cub *cub, t_ray *ray)
{
	if (ray->hor.intersected)
		ray->hor.dist = sqrt(pow((ray->hor.wall.x - cub->player.pos.x), 2)
				+ pow((ray->hor.wall.y - cub->player.pos.y), 2));
	else
		ray->hor.dist = DBL_MAX;
}

void	check_horizontal_intersection(t_cub *cub, t_ray *ray)
{
	t_intersection	tmp;

	ray->hor.intersected = 0;
	get_first_intersection(cub, &tmp, ray);
	get_steps(cub, &tmp, ray);
	if (!face_down(ray->angle))
		tmp.crd.y -= 1;
	while (inside_map(cub, tmp.crd.x, tmp.crd.y))
	{
		if (is_wall(cub, tmp.crd.x, tmp.crd.y))
		{
			if (!face_down(ray->angle))
				tmp.crd.y += 1;
			ray->hor.wall = (t_dpoint){.x = tmp.crd.x, .y = tmp.crd.y};
			ray->hor.intersected = 1;
			break ;
		}
		tmp.crd = (t_dpoint){.x = tmp.crd.x + tmp.step.x, .y = tmp.crd.y
			+ tmp.step.y};
	}
	get_distance(cub, ray);
}
