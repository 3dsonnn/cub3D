/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_init_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 05:58:16 by efinda            #+#    #+#             */
/*   Updated: 2025/01/17 11:27:58 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	set_tiles_colors(t_cub *cub, int i, int j)
{
	while (++i < cub->scene.map.size.y)
	{
		j = -1;
		while (++j < cub->scene.map.size.x)
		{
			if (cub->scene.map.content[i][j] == '1')
			{
				cub->minimap.tiles[i][j].id = '1';
				cub->minimap.tiles[i][j].color = 0x0000FF;
			}
			else if (cub->scene.map.content[i][j] == ' ')
			{
				cub->minimap.tiles[i][j].id = ' ';
				cub->minimap.tiles[i][j].color = 0xFFFFFF;
			}
			else
			{
				if (cub->scene.map.content[i][j] != '0')
					cub->minimap.tiles[i][j].id = 'E';
				cub->minimap.tiles[i][j].color = 0xD3D3D3;
			}
		}
	}
}

static int	init_horizontal_boundary_tiles_aux(t_cub *cub, int j)
{
	if (j == 0)
	{
		cub->minimap.tiles[0][j].pos.x0 = 0;
		cub->minimap.tiles[0][j].pos.x = cub->minimap.width
			+ cub->minimap.extra_width;
		cub->minimap.tiles[cub->scene.map.size.y - 1][j].pos.x0 = 0;
		cub->minimap.tiles[cub->scene.map.size.y
			- 1][j].pos.x = cub->minimap.tiles[0][j].pos.x;
		return (1);
	}
	if (j == cub->scene.map.size.x - 1)
	{
		cub->minimap.tiles[0][j].pos.x0 = MINIWIDTH - (cub->minimap.width
				+ cub->minimap.extra_width + (cub->minimap.remainder_width
					% 2));
		cub->minimap.tiles[0][j].pos.x = MINIWIDTH;
		cub->minimap.tiles[cub->scene.map.size.y
			- 1][j].pos.x0 = cub->minimap.tiles[0][j].pos.x0;
		cub->minimap.tiles[cub->scene.map.size.y - 1][j].pos.x = MINIWIDTH;
		return (1);
	}
	return (0);
}

static void	init_horizontal_boundary_tiles(t_cub *cub, int i, int j)
{
	while (++j < cub->scene.map.size.x)
	{
		cub->minimap.tiles[0][j].pos.y0 = 0;
		cub->minimap.tiles[0][j].pos.y = cub->minimap.height
			+ cub->minimap.extra_height;
		cub->minimap.tiles[0][j].down->pos.y0 = cub->minimap.tiles[0][j].pos.y;
		cub->minimap.tiles[cub->scene.map.size.y - 1][j].pos.y0 = MINIHEIGHT
			- (cub->minimap.height + cub->minimap.extra_height
				+ (cub->minimap.remainder_height % 2));
		cub->minimap.tiles[cub->scene.map.size.y - 1][j].pos.y = MINIHEIGHT;
		cub->minimap.tiles[cub->scene.map.size.y
			- 1][j].up->pos.y = cub->minimap.tiles[cub->scene.map.size.y
			- 1][j].pos.y0;
		if (init_horizontal_boundary_tiles_aux(cub, j))
			continue ;
		cub->minimap.tiles[0][j].pos.x0 = cub->minimap.tiles[0][j - 1].pos.x;
		cub->minimap.tiles[0][j].pos.x = cub->minimap.tiles[0][j].pos.x0
			+ cub->minimap.width;
		cub->minimap.tiles[cub->scene.map.size.y
			- 1][j].pos.x0 = cub->minimap.tiles[0][j].pos.x0;
		cub->minimap.tiles[cub->scene.map.size.y
			- 1][j].pos.x = cub->minimap.tiles[0][j].pos.x;
	}
}

static int	init_vertical_boundary_tiles_aux(t_cub *cub, int i)
{
	if (i == 0)
	{
		cub->minimap.tiles[i][0].pos.y0 = 0;
		cub->minimap.tiles[i][0].pos.y = cub->minimap.height
			+ cub->minimap.extra_height;
		cub->minimap.tiles[i][cub->scene.map.size.x - 1].pos.y0 = 0;
		cub->minimap.tiles[i][cub->scene.map.size.x
			- 1].pos.y = cub->minimap.tiles[i][0].pos.y;
		return (1);
	}
	if (i == cub->scene.map.size.y - 1)
	{
		cub->minimap.tiles[i][0].pos.y0 = MINIHEIGHT - (cub->minimap.height
				+ cub->minimap.extra_height + (cub->minimap.remainder_height
					% 2));
		cub->minimap.tiles[i][0].pos.y = MINIHEIGHT;
		cub->minimap.tiles[i][cub->scene.map.size.x
			- 1].pos.y0 = cub->minimap.tiles[i][0].pos.y0;
		cub->minimap.tiles[i][cub->scene.map.size.x - 1].pos.y = MINIHEIGHT;
		return (1);
	}
	return (0);
}

void	init_vertical_boundary_tiles(t_cub *cub, int i, int j, int wew)
{
	while (++i < cub->scene.map.size.y)
	{
		cub->minimap.tiles[i][0].pos.x0 = 0;
		cub->minimap.tiles[i][0].pos.x = wew;
		cub->minimap.tiles[i][0].next->pos.x0 = cub->minimap.tiles[i][0].pos.x;
		cub->minimap.tiles[i][cub->scene.map.size.x - 1].pos.x0 = MINIWIDTH
			- (wew + (cub->minimap.remainder_width % 2));
		cub->minimap.tiles[i][cub->scene.map.size.x - 1].pos.x = MINIWIDTH;
		cub->minimap.tiles[i][cub->scene.map.size.x
			- 1].prev->pos.x = cub->minimap.tiles[i][cub->scene.map.size.x
			- 1].pos.x0;
		if (init_vertical_boundary_tiles_aux(cub, i))
			continue ;
		cub->minimap.tiles[i][0].pos.y0 = cub->minimap.tiles[i - 1][0].pos.y;
		cub->minimap.tiles[i][0].pos.y = cub->minimap.tiles[i][0].pos.y0
			+ cub->minimap.height;
		cub->minimap.tiles[i][cub->scene.map.size.x
			- 1].pos.y0 = cub->minimap.tiles[i][0].pos.y0;
		cub->minimap.tiles[i][cub->scene.map.size.x
			- 1].pos.y = cub->minimap.tiles[i][0].pos.y;
	}
	init_horizontal_boundary_tiles(cub, -1, -1);
}
