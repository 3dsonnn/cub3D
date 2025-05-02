/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:20:38 by efinda            #+#    #+#             */
/*   Updated: 2025/05/02 04:35:24 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

// x/2 + x/3 = 3x+2x/6 = 5x/6

void	cub3d(t_cub *cub)
{
	get_rays(cub, -1);
	get_clear_and_crosshair_imgs(cub, cub->sprites.imgs);
	minimap(cub);
	if (is_door(cub->minimap.cur))
		my_mlx_put_img_to_img((t_img_to_img){.dst = &cub->img,
			.src = cub->scene.map.door.key, .aux = NULL,
			.dst_point = (t_point){.x = (cub->img.width
				- cub->scene.map.door.key.width) / 2, .y = (5 * cub->img.height)
			/ 6}, .src_point = (t_point){.x = 0, .y = 0},
			.size = (t_point){.x = cub->scene.map.door.key.width,
			.y = cub->scene.map.door.key.height}, .filter = 1,
			.color_aux = my_mlx_get_rgb_color(rand() % 256, rand() % 256, rand()
				% 256), .skip = 0});
}
