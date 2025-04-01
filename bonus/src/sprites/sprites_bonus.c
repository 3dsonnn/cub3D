/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 10:22:21 by efinda            #+#    #+#             */
/*   Updated: 2025/04/01 19:20:24 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static void	draw_health_bar(t_cub *cub, t_point bar_size, t_point iter)
{
	t_point	active;

	my_mlx_draw_horizontal_lines_to_img(&cub->img, (t_point){20,
		(cub->img.height - (bar_size.y + 20))}, (t_point){bar_size.x,
		bar_size.y}, DARK_GRAY);
	if (cub->sprites.health.value <= 0)
		return ;
	active.x = (bar_size.x * cub->sprites.health.value) / 100;
	active.y = cub->img.height - (bar_size.y + 20);
	while (++iter.y < 30)
	{
		iter.x = -1;
		while (++iter.x < active.x)
		{
			if (!iter.x || iter.x == 1 || iter.x + 1 == active.x || iter.x
				+ 2 == active.x || !iter.y || iter.y == 1 || iter.y + 1 == 30
				|| iter.y + 2 == 30)
				my_mlx_pixel_put(&cub->img, 20 + iter.x, active.y + iter.y,
					WHITE);
			else
				my_mlx_pixel_put(&cub->img, 20 + iter.x, active.y + iter.y,
					RED);
		}
	}
}

void	player(t_cub *cub)
{
	// draw_health_bar(cub, (t_point){300, 30}, (t_point){-1, -1});
	my_mlx_put_img_to_img(&cub->img, cub->sprites.imgs[CROSSHAIR],
		(t_point){(cub->img.width - cub->sprites.imgs[CROSSHAIR].width) / 2,
		(cub->img.height - cub->sprites.imgs[CROSSHAIR].height) / 2}, 1);
}
