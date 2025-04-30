/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_pixel_put_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcsilv <marcsilv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:18:08 by efinda            #+#    #+#             */
/*   Updated: 2025/04/30 13:30:36 by marcsilv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/my_mlx_bonus.h"

inline void	my_mlx_pixel_put(t_img *img, t_point crd, int color)
{
	if (!img || !img->addr || crd.x < 0 || crd.x >= img->width || crd.y < 0
		|| crd.y >= img->height)
		return ;
	*(img->addr + crd.y * img->line_len + crd.x) = color;
}
