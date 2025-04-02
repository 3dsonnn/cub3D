/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_init_img_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:46:07 by efinda            #+#    #+#             */
/*   Updated: 2025/04/01 16:03:46 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/my_mlx_bonus.h"

void    my_mlx_init_img(t_img *img)
{
    if (!img)
        return ;
    img->img = NULL;
    img->addr = NULL;
    img->line_len = 0;
    img->bpp = 0;
    img->endian = 0;
    img->width = 0;
    img->height = 0;
}
