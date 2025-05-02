/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcsilv <marcsilv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 10:22:21 by efinda            #+#    #+#             */
/*   Updated: 2025/05/02 13:50:20 by marcsilv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

void	get_clear_and_crosshair_imgs(t_cub *cub, t_img imgs[25])
{
	my_mlx_put_img_to_img((t_img_to_img){.dst = &imgs[CLEAR], .src = cub->img,
		.aux = NULL, .dst_point = (t_point){.x = 0, .y = 0},
		.src_point = (t_point){.x = cub->img.width / 2 + CROSSHAIR_SIZE,
		.y = cub->img.height - imgs[CLEAR].height},
		.size = (t_point){.x = imgs[CLEAR].width, .y = imgs[CLEAR].height},
		.filter = 0, .color_aux = TRANSPARENT, .skip = 0});
	my_mlx_put_img_to_img((t_img_to_img){.dst = &cub->img,
		.src = imgs[CROSSHAIR], .aux = NULL,
		.dst_point = (t_point){.x = cub->img.width / 2, .y = cub->img.height
		/ 2}, .src_point = (t_point){.x = 0, .y = 0},
		.size = (t_point){.x = imgs[CROSSHAIR].width,
		.y = imgs[CROSSHAIR].height}, .filter = 1, .color_aux = TRANSPARENT,
		.skip = 1});
}

void	put_shooting_animation(t_img *back, t_img frame, t_img clear)
{
	t_point	iter;
	t_point	start;
	int		color;

	iter = (t_point){-1, -1};
	start = (t_point){back->width / 2 + CROSSHAIR_SIZE,
		back->height - frame.height};
	while (++iter.y < frame.height)
	{
		iter.x = -1;
		while (++iter.x < frame.width)
		{
			color = my_mlx_get_pixel(frame, iter.x, iter.y);
			if (color == (int)TRANSPARENT || color == (int)BLACK)
				color = my_mlx_get_pixel(clear, iter.x, iter.y);
			my_mlx_pixel_put(back, start.x + iter.x, start.y + iter.y, color);
		}
	}
}

void	update_shooting_animation(t_img *back, t_sprite *sprites,
		unsigned long long cur_time)
{
	cur_time = get_current_time();
	if (cur_time - sprites->last_frame_time >= 35)
	{
		sprites->last_frame_time = cur_time;
		if (sprites->cur_frame <= SHELL_09)
		{
			put_shooting_animation(back, sprites->imgs[sprites->cur_frame],
				sprites->imgs[CLEAR]);
			sprites->i++;
			if (sprites->i % 2 == 0)
				sprites->cur_frame++;
		}
		else
		{
			sprites->shooting = false;
			sprites->idle = true;
			sprites->cur_frame = IDLE;
			put_shooting_animation(back, sprites->imgs[IDLE],
				sprites->imgs[CLEAR]);
		}
	}
}
