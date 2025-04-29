/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcsilv <marcsilv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:20:38 by efinda            #+#    #+#             */
/*   Updated: 2025/04/29 12:50:53 by marcsilv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

// x/2 + x/3 = 3x+2x/6 = 5x/6

void	cub3D(t_cub *cub)
{
	get_rays(cub, -1);
	my_mlx_put_img_to_img((t_img_to_img){
		.dst = &cub->sprites.imgs[CLEAR],
		.src = cub->img,
		.aux = NULL,
		.dst_point = (t_point){.x = 0, .y = 0},
		.src_point = (t_point){.x = cub->img.width / 2, .y = cub->img.height - cub->sprites.imgs[CLEAR].height},
		.size = (t_point){.x = cub->sprites.imgs[CLEAR].width, .y = cub->sprites.imgs[CLEAR].height},
		.filter = 0,
		.color_aux = TRANSPARENT,
		.color = 0
	});
	// mlx_put_image_to_window(cub->mlx, cub->win, cub->sprites.imgs[CLEAR].img, 0, 0);
	minimap(cub);
	player(cub);
	if (is_door(cub->minimap.cur))
		my_mlx_put_img_to_img((t_img_to_img){
			.dst = &cub->img,
			.src = cub->scene.map.door.key,
			.aux = NULL,
			.dst_point = (t_point){.x = (cub->img.width - cub->scene.map.door.key.width) / 2, .y = (5 * cub->img.height) / 6},
			.src_point = (t_point){.x = 0, .y = 0},
			.size = (t_point){.x = cub->scene.map.door.key.width, .y = cub->scene.map.door.key.height},
			.filter = 1,
			.color_aux = my_mlx_get_rgb_color(rand() % 256, rand() % 256, rand() % 256),
			.color = 0
		});
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
	// mlx_put_image_to_window(cub->mlx, cub->win, cub->minimap.img.img, 10, 10);
	draw_filled_triangle(cub->mlx, cub->win, 10 + 10 + CIRCLE_RADIUS, 10 + 10 + CIRCLE_RADIUS, TRIANGLE_SIZE, YELLOW);

	// mlx_put_image_to_window(cub->mlx, cub->win,
	// 	cub->sprites.imgs[HEALTH_BAR].img, 20, HEIGHT - 20
	// 	- cub->sprites.imgs[HEALTH_BAR].height);
}
