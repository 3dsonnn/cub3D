/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:22:29 by efinda            #+#    #+#             */
/*   Updated: 2025/04/30 17:55:09 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static void	get_first_intersection(t_cub *cub, t_ray *ray, t_intersection *tmp)
{
	tmp->crd.y = floor(cub->player.pos.y / TILE) * TILE;
	if (face_down(ray->angle))
		tmp->crd.y += TILE;
	tmp->crd.x = cub->player.pos.x + ((tmp->crd.y - cub->player.pos.y)
			/ ray->tan);
}

static void	get_steps(t_ray *ray, t_intersection *tmp)
{
	tmp->step.y = TILE;
	if (!face_down(ray->angle))
		tmp->step.y *= -1;
	tmp->step.x = TILE / ray->tan;
	if ((!face_right(ray->angle) && tmp->step.x > 0) || (face_right(ray->angle)
			&& tmp->step.x < 0))
		tmp->step.x *= -1;
}

static void	get_distance(t_cub *cub, t_ray *ray)
{
	if (ray->hor.intersected)
		ray->hor.dist = sqrt(pow((ray->hor.wall.x - cub->player.pos.x), 2)
				+ pow((ray->hor.wall.y - cub->player.pos.y), 2));
	else
		ray->hor.dist = DBL_MAX;
}

void	check_horizontal_intersection(t_cub *cub, t_ray *ray, int check_wall)
{
	t_intersection	tmp;

	ray->hor.intersected = 0;
	get_first_intersection(cub, ray, &tmp);
	get_steps(ray, &tmp);
	if (!face_down(ray->angle))
		tmp.crd.y -= 1;
	while (inside_map(cub, tmp.crd.x, tmp.crd.y))
	{
		check_wall = is_wall(cub, tmp.crd.x, tmp.crd.y);
		if (check_wall)
		{
			if (!face_down(ray->angle))
				tmp.crd.y += 1;
			ray->hor.wall = (t_dpoint){.x = tmp.crd.x, .y = tmp.crd.y};
			ray->hor.intersected = 1;
			if (check_wall == 2)
				ray->hor.is_door = 1;
			break ;
		}
		tmp.crd = (t_dpoint){.x = tmp.crd.x + tmp.step.x, .y = tmp.crd.y
			+ tmp.step.y};
	}
	get_distance(cub, ray);
}
