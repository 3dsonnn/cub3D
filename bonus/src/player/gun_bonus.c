/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 09:19:18 by efinda            #+#    #+#             */
/*   Updated: 2025/04/01 13:13:40 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

// void	put_gun_frame(t_cub *cub, t_img frame)
// {
// 	t_point	iter;
// 	int		color;

// 	iter.y = -1;
// 	while (++iter.y < GUN_HEIGHT)
// 	{
// 		iter.x = -1;
// 		while (++iter.x < GUN_WIDTH)
// 		{
// 			color = my_mlx_get_pixel(frame, iter.x, iter.y);
// 			if (color == TRANSPARENT)
// 				color = my_mlx_get_pixel(cub->player.imgs[CLEAR], iter.x,
// 						iter.y);
// 			my_mlx_pixel_put(&cub->img, HALF_WIDTH + iter.x, HEIGHT - GUN_HEIGHT
// 				+ iter.y, color);
// 			iter.x++;
// 		}
// 		iter.y++;
// 	}
// }
