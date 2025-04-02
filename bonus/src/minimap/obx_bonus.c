/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obx_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 22:51:48 by efinda            #+#    #+#             */
/*   Updated: 2025/04/02 00:47:54 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static void	edge_cases(t_cub *cub, t_tile *corners[4], t_tile **tiles,
		t_plane plane)
{
	if (!corners[TOPRIGHT]->right && (plane.x - 10) >= 0)
	{
		corners[TOPLEFT] = &tiles[plane.y0][plane.x - 10];
		cub->minimap.bounds.x = 10;
	}
	if (!corners[BOTTLEFT]->down && (plane.y - 10) >= 0)
	{
		corners[TOPLEFT] = &tiles[plane.y - 10][plane.x0];
		cub->minimap.bounds.y = 10;
	}
	if (!corners[BOTTRIGHT]->right && (plane.x - 10) >= 0)
	{
		corners[TOPLEFT] = &tiles[corners[TOPLEFT]->crd.y][plane.x - 10];
		cub->minimap.bounds.x = 10;
	}
}

static t_plane	get_indexes(t_cub *cub, t_tile *cur, t_tile *tmp[4],
		t_iter iter)
{
	while (++(iter.i) < 5 && cur && cur->up)
		tmp[0] = cur = cur->up;
	cur = cub->minimap.cur;
	while (++(iter.j) < 5 && cur && cur->down)
		tmp[1] = cur = cur->down;
	cur = cub->minimap.cur;
	while (++(iter.k) < 5 && cur && cur->left)
		tmp[2] = cur = cur->left;
	cur = cub->minimap.cur;
	while (++(iter.l) < 5 && cur && cur->right)
		tmp[3] = cur = cur->right;
	return ((t_plane){tmp[2]->crd.x, tmp[3]->crd.x, tmp[0]->crd.y,
		tmp[1]->crd.y});
}

void	update_obx(t_cub *cub, t_tile *corners[4], t_tile **tiles)
{
	t_plane	plane;

	if (!cub->minimap.box)
		return ;
	plane = get_indexes(cub, cub->minimap.cur, (t_tile *[]){cub->minimap.cur,
			cub->minimap.cur, cub->minimap.cur, cub->minimap.cur}, (t_iter){-1,
			-1, -1, -1, -1, -1});
	corners[TOPLEFT] = &tiles[plane.y0][plane.x0];
	corners[TOPRIGHT] = &tiles[plane.y0][plane.x];
	corners[BOTTLEFT] = &tiles[plane.y][plane.x0];
	corners[BOTTRIGHT] = &tiles[plane.y][plane.x];
	cub->minimap.bounds.x = abs(plane.x - plane.x0);
	cub->minimap.bounds.y = abs(plane.y - plane.y0);
	edge_cases(cub, corners, tiles, plane);
}
