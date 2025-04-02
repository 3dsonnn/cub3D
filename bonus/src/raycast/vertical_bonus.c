/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:22:29 by efinda            #+#    #+#             */
/*   Updated: 2025/04/01 20:26:37 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static void	get_first_intersection(t_cub *cub, t_ray *ray, t_intersection *tmp)
{
	tmp->crd.x = floor(cub->player.pos.x / TILE) * TILE;
	if (face_right(ray->angle))
		tmp->crd.x += TILE;
	tmp->crd.y = cub->player.pos.y + ((tmp->crd.x - cub->player.pos.x)
			* ray->tan);
}

static void	get_steps(t_cub *cub, t_ray *ray, t_intersection *tmp)
{
	tmp->step.x = TILE;
	if (!face_right(ray->angle))
		tmp->step.x *= -1;
	tmp->step.y = TILE * ray->tan;
	if ((!face_down(ray->angle) && tmp->step.y > 0) || (face_down(ray->angle)
			&& tmp->step.y < 0))
		tmp->step.y *= -1;
}

void	check_vertical_intersection(t_cub *cub, t_ray *ray)
{
	t_intersection	tmp;

	ray->ver.dist = DBL_MAX;
	ray->ver.intersected = 0;
	get_first_intersection(cub, ray, &tmp);
	get_steps(cub, ray, &tmp);
	if (!face_right(ray->angle))
		tmp.crd.x -= 1;
	while (inside_map(cub, tmp.crd.x, tmp.crd.y))
	{
		if (is_wall(cub, tmp.crd.x, tmp.crd.y))
		{
			if (!face_right(ray->angle))
				tmp.crd.x += 1;
			ray->ver.wall.x = tmp.crd.x;
			ray->ver.wall.y = tmp.crd.y;
			ray->ver.intersected = 1;
			break ;
		}
		tmp.crd.x += tmp.step.x;
		tmp.crd.y += tmp.step.y;
	}
	if (ray->ver.intersected)
		ray->ver.dist = sqrt(pow((ray->ver.wall.x - cub->player.pos.x), 2)
				+ pow((ray->ver.wall.y - cub->player.pos.y), 2));
}
