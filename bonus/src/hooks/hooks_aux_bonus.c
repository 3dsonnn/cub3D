/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_aux_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 19:10:28 by efinda            #+#    #+#             */
/*   Updated: 2025/04/27 12:21:49 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

inline void	alt_space(t_cub *cub, int keycode)
{
	if (keycode == ALT)
	{
		if (cub->hooks.alt)
			mlx_mouse_hide(cub->mlx, cub->win);
		else
			mlx_mouse_show(cub->mlx, cub->win);
		cub->hooks.alt = !cub->hooks.alt;
	}
	else
	{
		if (cub->hooks.space)
			mlx_do_key_autorepeatoff(cub->mlx);
		else
			mlx_do_key_autorepeaton(cub->mlx);
		cub->hooks.space = !cub->hooks.space;
	}
}

void	update_frame(t_img *back, t_sprite *sprites, unsigned long long current_time)
{
	current_time = get_current_time();
	if (current_time - sprites->last_frame_time >= 35)
	{
		sprites->last_frame_time = current_time;
		if (sprites->cur_frame_index <= SHELL_08)
		{
			my_mlx_put_img_to_img((t_img_to_img){
				.dst = back,
				.src = sprites->imgs[sprites->cur_frame_index],
				.aux = &sprites->imgs[CLEAR],
				.dst_point = (t_point){.x = back->width / 2, .y = back->height - sprites->imgs[CLEAR].height},
				.src_point = (t_point){.x = 0, .y = 0},
				.size = (t_point){.x = sprites->imgs[CLEAR].width, .y = sprites->imgs[CLEAR].height},
				.filter = 1,
				.color_aux = TRANSPARENT,
				.color = 0
			});
			sprites->i++;
			if (sprites->i % 2 == 0)
				sprites->cur_frame_index++;
		}
		else
		{
			sprites->shooting = false;
			sprites->idle = true;
			sprites->cur_frame_index = IDLE;
			my_mlx_put_img_to_img((t_img_to_img){
				.dst = back,
				.src = sprites->imgs[sprites->cur_frame_index],
				.aux = &sprites->imgs[CLEAR],
				.dst_point = (t_point){.x = back->width / 2, .y = back->height - sprites->imgs[CLEAR].height},
				.src_point = (t_point){.x = 0, .y = 0},
				.size = (t_point){.x = sprites->imgs[CLEAR].width, .y = sprites->imgs[CLEAR].height},
				.filter = 1,
				.color_aux = TRANSPARENT,
				.color = 0
			});
		}
	}
}
