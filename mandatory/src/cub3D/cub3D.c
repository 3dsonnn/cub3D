/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:20:38 by efinda            #+#    #+#             */
/*   Updated: 2025/03/13 09:17:56 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	choose_intersection(t_cub *cub, int i)
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

static void	get_column(t_cub *cub, int i)
{
	cub->rays[i].col.dist = cub->rays[i].dist
		* cos(ft_normalizer(cub->rays[i].angle - cub->player.angle));
	cub->rays[i].col.height = (int)(TILE / cub->rays[i].col.dist * cub->ppd);
	cub->rays[i].col.top = (int)(cub->img.height - cub->rays[i].col.height) / 2;
	// if (cub->rays[i].col.top < 0)
	//     cub->rays[i].col.top = 0;
	cub->rays[i].col.bot = (int)(cub->img.height + cub->rays[i].col.height) / 2;
	if (cub->rays[i].col.bot > cub->img.height)
		cub->rays[i].col.bot = cub->img.height;
}

void	cub3d(t_cub *cub, int j)
{
	while (++j < cub->img.width)
	{
		cub->rays[j].angle = cub->player.angle + atan((j - cub->img.width / 2)
				/ cub->ppd);
		cub->rays[j].angle = ft_normalizer(cub->rays[j].angle);
		cub->rays[j].tan = tan(cub->rays[j].angle);
		check_horizontal_intersection(cub, j);
		check_vertical_intersection(cub, j);
		choose_intersection(cub, j);
		get_column(cub, j);
		cub->rays[j].texture = get_texture(cub, cub->rays[j].angle,
				cub->rays[j].dir);
		paint(cub, -1, j, (t_point){0, 0});
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
}
