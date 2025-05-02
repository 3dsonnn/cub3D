/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_new_img_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:34:20 by efinda            #+#    #+#             */
/*   Updated: 2025/04/30 18:14:24 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/my_mlx_bonus.h"

void	my_mlx_new_img(void *mlx, t_img *img, t_point size)
{
	if (!mlx || !img || size.x <= 0 || size.y <= 0)
		return ;
	img->img = mlx_new_image(mlx, size.x, size.y);
	if (!img->img)
		return ;
	img->width = size.x;
	img->height = size.y;
}
