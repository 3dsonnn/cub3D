/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_duplicate_img.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:32:07 by efinda            #+#    #+#             */
/*   Updated: 2025/04/30 18:13:56 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/my_mlx_bonus.h"

void	my_mlx_duplicate_img(void *mlx, t_img *dst, t_img src)
{
	if (!mlx || src.height <= 0 || src.width <= 0)
		return ;
	my_mlx_init_img(dst);
	my_mlx_new_img(mlx, dst, (t_point){src.width, src.height});
	if (!dst->img)
		return ;
	my_mlx_get_data_addr(dst);
	if (!dst->addr)
		my_mlx_destroy_img(mlx, dst);
}
