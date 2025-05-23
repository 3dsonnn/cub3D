/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:22:29 by efinda            #+#    #+#             */
/*   Updated: 2025/04/30 17:43:36 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	get_first_intersection(t_cub *cub, t_intersection *tmp, t_ray *ray)
{
	tmp->crd.x = floor(cub->player.pos.x / TILE) * TILE;
	if (face_right(ray->angle))
		tmp->crd.x += TILE;
	tmp->crd.y = cub->player.pos.y + ((tmp->crd.x - cub->player.pos.x)
			* ray->tan);
}

static void	get_steps(t_intersection *tmp, t_ray *ray)
{
	tmp->step.x = TILE;
	if (!face_right(ray->angle))
		tmp->step.x *= -1;
	tmp->step.y = TILE * ray->tan;
	if ((!face_down(ray->angle) && tmp->step.y > 0) || (face_down(ray->angle)
			&& tmp->step.y < 0))
		tmp->step.y *= -1;
}

static void	get_distance(t_cub *cub, t_ray *ray)
{
	if (ray->ver.intersected)
		ray->ver.dist = sqrt(pow((ray->ver.wall.x - cub->player.pos.x), 2)
				+ pow((ray->ver.wall.y - cub->player.pos.y), 2));
	else
		ray->ver.dist = DBL_MAX;
}

void	check_vertical_intersection(t_cub *cub, t_ray *ray)
{
	t_intersection	tmp;

	ray->ver.intersected = 0;
	get_first_intersection(cub, &tmp, ray);
	get_steps(&tmp, ray);
	if (!face_right(ray->angle))
		tmp.crd.x -= 1;
	while (inside_map(cub, tmp.crd.x, tmp.crd.y))
	{
		if (is_wall(cub, tmp.crd.x, tmp.crd.y))
		{
			if (!face_right(ray->angle))
				tmp.crd.x += 1;
			ray->ver.wall = (t_dpoint){.x = tmp.crd.x, .y = tmp.crd.y};
			ray->ver.intersected = 1;
			break ;
		}
		tmp.crd = (t_dpoint){.x = tmp.crd.x + tmp.step.x, .y = tmp.crd.y
			+ tmp.step.y};
	}
	get_distance(cub, ray);
}
