/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 22:59:10 by efinda            #+#    #+#             */
/*   Updated: 2025/03/13 02:22:01 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static  inline  int map(int old_value, int old_min, int old_max, int new_min, int new_max)
{
    double old_range = old_max - old_min;
    double new_range = new_max - new_min;
    double ratio = (double)(old_value - old_min) / old_range;
    return (int)(new_min + ratio * new_range);
}

static void miniplayer(t_cub *cub, t_dpoint player_pos, t_point cur_crd)
{
    t_bresenham_line line;
    line.img = &cub->img;
    
    int base_x = cur_crd.x * cub->minimap.tilesize + 10;
    int base_y = cur_crd.y * cub->minimap.tilesize + 10;

    int tile_x_min = ((int)cub->player.pos.x / TILE) * TILE;
    int tile_y_min = ((int)cub->player.pos.y / TILE) * TILE;

    line.crd.x0 = map((int)cub->player.pos.x, tile_x_min, tile_x_min + TILE, 
                      base_x, base_x + cub->minimap.tilesize);
    line.crd.y0 = map((int)cub->player.pos.y, tile_y_min, tile_y_min + TILE, 
                      base_y, base_y + cub->minimap.tilesize);
    line.crd.x = line.crd.x0 + cub->player.dir.x * 10;
    line.crd.y = line.crd.y0 + cub->player.dir.y * 10;
    bresenham_line(line);
    line.crd.x0++;
    line.crd.x++;
    bresenham_line(line);
    line.crd.y0++;
    line.crd.y++;
    bresenham_line(line);
}

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
    miniplayer(cub, cub->player.pos, cub->minimap.cur->crd);
}
