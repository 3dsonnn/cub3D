/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 02:08:03 by efinda            #+#    #+#             */
/*   Updated: 2025/01/17 11:19:37 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	init_tiles(t_cub *cub, int i, int j)
{
	init_vertical_boundary_tiles(cub, -1, -1, cub->minimap.width
		+ cub->minimap.extra_width);
	while (++i < cub->scene.map.size.y - 1)
	{
		j = 0;
		while (++j < cub->scene.map.size.x - 1)
		{
			cub->minimap.tiles[i][j].id = '\0';
			cub->minimap.tiles[i][j].pos.x0 = cub->minimap.tiles[i][j].prev->pos.x;
			cub->minimap.tiles[i][j].pos.x = cub->minimap.tiles[i][j].pos.x0
				+ cub->minimap.width;
			cub->minimap.tiles[i][j].next->pos.x0 = cub->minimap.tiles[i][j].pos.x;
			cub->minimap.tiles[i][j].pos.y0 = cub->minimap.tiles[i][j].up->pos.y;
			cub->minimap.tiles[i][j].pos.y = cub->minimap.tiles[i][j].pos.y0
				+ cub->minimap.height;
			cub->minimap.tiles[i][j].down->pos.y0 = cub->minimap.tiles[i][j].pos.y;
		}
	}
	set_tiles_colors(cub, -1, -1);
}

static void	link_horizontal_boundary_tiles(t_cub *cub, int i, int j)
{
	while (++j < cub->scene.map.size.x)
	{
		cub->minimap.tiles[0][j].up = NULL;
		cub->minimap.tiles[0][j].down = &cub->minimap.tiles[1][j];
		if (j != 0)
		{
			cub->minimap.tiles[0][j].prev = &cub->minimap.tiles[0][j - 1];
			cub->minimap.tiles[cub->scene.map.size.y
				- 1][j].prev = &cub->minimap.tiles[cub->scene.map.size.y - 1][j
				- 1];
		}
		if (j != cub->scene.map.size.x - 1)
		{
			cub->minimap.tiles[0][j].next = &cub->minimap.tiles[0][j + 1];
			cub->minimap.tiles[cub->scene.map.size.y - 1][j].down = NULL;
			cub->minimap.tiles[cub->scene.map.size.y
				- 1][j].up = &cub->minimap.tiles[cub->scene.map.size.y - 2][j];
			cub->minimap.tiles[cub->scene.map.size.y
				- 1][j].next = &cub->minimap.tiles[cub->scene.map.size.y - 1][j
				+ 1];
		}
	}
}

static void	link_vertical_boundary_tiles(t_cub *cub, int i, int j)
{
	while (++i < cub->scene.map.size.y)
	{
		cub->minimap.tiles[i][0].prev = NULL;
		cub->minimap.tiles[i][0].next = &cub->minimap.tiles[i][1];
		if (i != 0)
		{
			cub->minimap.tiles[i][0].up = &cub->minimap.tiles[i - 1][0];
			cub->minimap.tiles[i][cub->scene.map.size.x
				- 1].up = &cub->minimap.tiles[i - 1][cub->scene.map.size.x - 1];
		}
		if (i != cub->scene.map.size.y - 1)
		{
			cub->minimap.tiles[i][0].down = &cub->minimap.tiles[i + 1][0];
			cub->minimap.tiles[i][cub->scene.map.size.x - 1].next = NULL;
			cub->minimap.tiles[i][cub->scene.map.size.x
				- 1].prev = &cub->minimap.tiles[i][cub->scene.map.size.x - 2];
			cub->minimap.tiles[i][cub->scene.map.size.x
				- 1].down = &cub->minimap.tiles[i + 1][cub->scene.map.size.x
				- 1];
		}
	}
	link_horizontal_boundary_tiles(cub, -1, -1);
}

static void	link_tiles(t_cub *cub, int i, int j)
{
	link_vertical_boundary_tiles(cub, -1, -1);
	while (++i < cub->scene.map.size.y - 1)
	{
		j = -1;
		while (++j < cub->scene.map.size.x - 1)
		{
			cub->minimap.tiles[i][j].prev = &cub->minimap.tiles[i][j - 1];
			cub->minimap.tiles[i][j].next = &cub->minimap.tiles[i][j + 1];
			cub->minimap.tiles[i][j].up = &cub->minimap.tiles[i - 1][j];
			cub->minimap.tiles[i][j].down = &cub->minimap.tiles[i + 1][j];
		}
	}
}

void	init_minimap(t_cub *cub, int i, int j)
{
	cub->minimap.width = (int)floor(MINIWIDTH / cub->scene.map.size.x);
	cub->minimap.height = (int)floor(MINIHEIGHT / cub->scene.map.size.y);
	cub->minimap.img.img = mlx_new_image(cub->mlx, MINIWIDTH, MINIHEIGHT);
	cub->minimap.img.addr = mlx_get_data_addr(cub->minimap.img.img,
			&cub->minimap.img.bpp, &cub->minimap.img.line_len,
			&cub->minimap.img.endian);
	cub->minimap.tiles = (t_tile **)malloc(sizeof(t_tile *)
			* (cub->scene.map.size.y));
	while (++i < cub->scene.map.size.y)
	{
		cub->minimap.tiles[i] = (t_tile *)malloc(sizeof(t_tile)
				* cub->scene.map.size.x);
		cub->minimap.tiles[i]->up = NULL;
		cub->minimap.tiles[i]->down = NULL;
		cub->minimap.tiles[i]->prev = NULL;
		cub->minimap.tiles[i]->next = NULL;
	}
	link_tiles(cub, 0, 0);
	cub->minimap.remainder_width = MINIWIDTH - (cub->minimap.width
			* cub->scene.map.size.x);
	cub->minimap.remainder_height = MINIHEIGHT - (cub->minimap.height
			* cub->scene.map.size.y);
	cub->minimap.extra_width = cub->minimap.remainder_width / 2;
	cub->minimap.extra_height = cub->minimap.remainder_height / 2;
	init_tiles(cub, 0, 0);
	for (int i = -1; ++i < cub->scene.map.size.y;)
	{
		for (int j = -1; ++j < cub->scene.map.size.x;)
		{
			printf("color=%d\tx0[%d][%d]=%d\tx[%d][%d]=%d\ty0[%d][%d]=%d\ty[%d][%d]=%d\n",
				cub->minimap.tiles[i][j].color, i, j,
				cub->minimap.tiles[i][j].pos.x0, i, j,
				cub->minimap.tiles[i][j].pos.x, i, j,
				cub->minimap.tiles[i][j].pos.y0, i, j,
				cub->minimap.tiles[i][j].pos.y);
		}
	}
}
