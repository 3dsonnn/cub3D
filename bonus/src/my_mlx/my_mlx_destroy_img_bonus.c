/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_destroy_img_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:49:00 by efinda            #+#    #+#             */
/*   Updated: 2025/04/01 16:50:56 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/my_mlx_bonus.h"

void	my_mlx_destroy_img(void *mlx, t_img *img)
{
	if (mlx && img && img->img)
	{
		mlx_destroy_image(mlx, img->img);
        my_mlx_init_img(img);
	}
}
