/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 08:54:06 by efinda            #+#    #+#             */
/*   Updated: 2025/03/23 13:02:47 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

void	player(t_cub *cub)
{
	my_mlx_draw_ret_to_img(&cub->img, (t_point){10, cub->img.height - 40},
		(t_point){300, 30}, DARK_GRAY);
	my_mlx_draw_ret_to_img(&cub->img, (t_point){10, cub->img.height - 40},
		(t_point){((300 * cub->player.health.value) / 100), 30}, RED);
	my_mlx_put_img_to_img(&cub->img, cub->player.imgs[CROSSHAIR],
		(t_point){(cub->img.width - cub->player.imgs[CROSSHAIR].width) / 2,
		(cub->img.height - cub->player.imgs[CROSSHAIR].height) / 2}, 1);
    // draw_shotgun(cub);
}
