/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_init_img_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:46:07 by efinda            #+#    #+#             */
/*   Updated: 2025/04/30 18:17:25 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/my_mlx_bonus.h"

void	my_mlx_init_img(t_img *img)
{
	if (!img)
		return ;
	*img = (t_img){.img = NULL, .addr = NULL, .line_len = 0, .bpp = 0,
		.endian = 0, .width = 0, .height = 0};
}
