/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_refresh.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 09:37:34 by efinda            #+#    #+#             */
/*   Updated: 2025/01/17 12:47:20 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void    refresh_minimap(t_cub *cub, int i, int j)
{
    while (++i < cub->size.y)
	{
		j = -1;
		while (++j < cub->size.y)
		{
			if (cub->minimap.tiles[i][j].id == 'E')
			{
                cub->player.i = i;
                cub->player.j = j;
                if (cub->player.pos.x0 >= cub->minimap.tiles[i][j].pos.x0)
                {
                    cub->minimap.tiles[i][j].id == '\0';
                    cub->minimap.tiles[i][j + 1].id == 'E';
                }
                else if (cub->player.pos.x0 <= cub->minimap.tiles[i][j].pos.x0)
                {
                    cub->minimap.tiles[i][j].id == '\0';
                    cub->minimap.tiles[i][j - 1].id == 'E';
                }
                else if (cub->player.pos.y0 >= cub->minimap.tiles[i][j].pos.y0)
                {
                    cub->minimap.tiles[i][j].id == '\0';
                    cub->minimap.tiles[i + 1][j].id == 'E';
                }
                else if (cub->player.pos.y0 <= cub->minimap.tiles[i][j].pos.y0)
                {
                    cub->minimap.tiles[i][j].id == '\0';
                    cub->minimap.tiles[i - 1][j].id == 'E';
                }
			}
		}
	}
}
