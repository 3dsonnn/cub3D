/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_aux_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:37:22 by efinda            #+#    #+#             */
/*   Updated: 2025/03/22 00:06:05 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

void    my_mlx_put_img_to_img(t_img *dst, t_img src, int x, int y)
{
    t_point src_iter;
    t_plane dst_iter;

    if (!dst || x < 0 || x >= dst->width || y < 0 || y >= dst->height)
        return ;
    dst_iter = (t_plane){x, x, y, y};
    src_iter.y = -1;
    while (++src_iter.y < src.height)
    {
        src_iter.x = -1;
        dst_iter.x = dst_iter.x0;
        while (++src_iter.x < src.width)
        {
            my_mlx_pixel_put(dst, dst_iter.x, dst_iter.y, my_mlx_get_pixel(src, src_iter.x, src_iter.y));
            dst_iter.x++;
        }
        dst_iter.y++;
    }
}
