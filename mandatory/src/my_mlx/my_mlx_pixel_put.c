/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_pixel_put.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:18:08 by efinda            #+#    #+#             */
/*   Updated: 2025/04/16 23:45:49 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/my_mlx.h"

inline void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	if (!img || !img->addr || x < 0 || x >= img->width || y < 0
		|| y >= img->height)
		return ;
	*(img->addr + y * img->line_len + x) = color;
}
