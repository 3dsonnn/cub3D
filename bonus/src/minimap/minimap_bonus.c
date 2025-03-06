/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 22:59:10 by efinda            #+#    #+#             */
/*   Updated: 2025/03/06 00:57:07 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

void    minimap(t_cub *cub, int i, int j)
{
    if (cub->minimap.box)
        paint_obx(cub, cub->minimap.corners[TOPLEFT]);
    else
    {
        i = -1;
		while (++i < cub->scene.map.size.y)
		{
			j = -1;
			while (++j < cub->scene.map.size.x)
            {
                if (cub->minimap.tiles[i][j].id == ' ')
				    ;
                else
				    paint_minimap_tile(cub, i, j, cub->minimap.tiles[i][j].color);
            }
		}
    }
}
