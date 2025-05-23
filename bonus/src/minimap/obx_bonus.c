/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obx_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 22:51:48 by efinda            #+#    #+#             */
/*   Updated: 2025/04/30 18:20:08 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static t_plane	get_indexes(t_cub *cub, t_tile *cur, t_tile *tmp[4],
		t_iter iter)
{
	while (++(iter.i) < 5 && cur && cur->up)
	{
		tmp[0] = cur;
		cur = cur->up;
	}
	cur = cub->minimap.cur;
	while (++(iter.j) < 5 && cur && cur->down)
	{
		tmp[1] = cur;
		cur = cur->down;
	}
	cur = cub->minimap.cur;
	while (++(iter.k) < 5 && cur && cur->left)
	{
		tmp[2] = cur;
		cur = cur->left;
	}
	cur = cub->minimap.cur;
	while (++(iter.l) < 5 && cur && cur->right)
	{
		tmp[3] = cur;
		cur = cur->right;
	}
	return ((t_plane){tmp[2]->crd.x, tmp[3]->crd.x, tmp[0]->crd.y,
		tmp[1]->crd.y});
}

void	update_obx(t_cub *cub, t_tile *corners[4], t_tile **tiles)
{
	t_plane	plane;

	plane = get_indexes(cub, cub->minimap.cur, (t_tile *[]){cub->minimap.cur,
			cub->minimap.cur, cub->minimap.cur, cub->minimap.cur}, (t_iter){-1,
			-1, -1, -1, -1, -1});
	corners[TOPLEFT] = &tiles[plane.y0][plane.x0];
	corners[TOPRIGHT] = &tiles[plane.y0][plane.x];
	corners[BOTTLEFT] = &tiles[plane.y][plane.x0];
	corners[BOTTRIGHT] = &tiles[plane.y][plane.x];
}
