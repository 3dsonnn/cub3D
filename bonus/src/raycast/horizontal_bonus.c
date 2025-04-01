/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:22:29 by efinda            #+#    #+#             */
/*   Updated: 2025/04/01 20:27:25 by efinda           ###   ########.fr       */
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

static void	get_steps(t_cub *cub, t_ray *ray, t_intersection *tmp)
{
	tmp->step.y = TILE;
	if (!face_down(ray->angle))
		tmp->step.y *= -1;
	tmp->step.x = TILE / ray->tan;
	if ((!face_right(ray->angle) && tmp->step.x > 0) || (face_right(ray->angle)
			&& tmp->step.x < 0))
		tmp->step.x *= -1;
}

void	check_horizontal_intersection(t_cub *cub, t_ray *ray)
{
	t_intersection	tmp;

	ray->hor.dist = DBL_MAX;
	ray->hor.intersected = 0;
	get_first_intersection(cub, ray, &tmp);
	get_steps(cub, ray, &tmp);
	if (!face_down(ray->angle))
		tmp.crd.y -= 1;
	while (inside_map(cub, tmp.crd.x, tmp.crd.y))
	{
		if (is_wall(cub, tmp.crd.x, tmp.crd.y))
		{
			if (!face_down(ray->angle))
				tmp.crd.y += 1;
			ray->hor.wall.x = tmp.crd.x;
			ray->hor.wall.y = tmp.crd.y;
			ray->hor.intersected = 1;
			break ;
		}
		tmp.crd.x += tmp.step.x;
		tmp.crd.y += tmp.step.y;
	}
	if (ray->hor.intersected)
		ray->hor.dist = sqrt(pow((ray->hor.wall.x - cub->player.pos.x), 2)
				+ pow((ray->hor.wall.y - cub->player.pos.y), 2));
}
