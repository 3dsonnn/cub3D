/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounding_box.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:55:56 by efinda            #+#    #+#             */
/*   Updated: 2025/02/10 15:10:55 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static t_plane	get_corners_indexes(t_cub *cub, t_tile *cur, t_plane plane,
		t_iter iter)
{
	t_tile	*tmp[4];

	tmp[0] = cur;
	tmp[1] = cur;
	tmp[2] = cur;
	tmp[3] = cur;
	while (++(iter.i) < 5 && cur && cur->up)
		tmp[0] = cur = cur->up;
	cur = cub->cur;
	while (++(iter.j) < 5 && cur && cur->down)
		tmp[1] = cur = cur->down;
	cur = cub->cur;
	while (++(iter.k) < 5 && cur && cur->left)
		tmp[2] = cur = cur->left;
	cur = cub->cur;
	while (++(iter.l) < 5 && cur && cur->right)
		tmp[3] = cur = cur->right;
	plane.x0 = tmp[2]->crd.x;
	plane.x = tmp[3]->crd.x;
	plane.y0 = tmp[0]->crd.y;
	plane.y = tmp[1]->crd.y;
	return (plane);
}

void	update_corners(t_cub *cub)
{
	t_plane	plane;

	if (!cub->minimap.box)
		return ;
	plane = get_corners_indexes(cub, cub->cur, (t_plane){0, 0, 0, 0},
			(t_iter){-1, -1, -1, -1, -1, -1});
	cub->minimap.corners[TOPLEFT] = &cub->minimap.tiles[plane.y0][plane.x0];
	cub->minimap.corners[TOPRIGHT] = &cub->minimap.tiles[plane.y0][plane.x];
	cub->minimap.corners[BOTTLEFT] = &cub->minimap.tiles[plane.y][plane.x0];
	cub->minimap.corners[BOTTRIGHT] = &cub->minimap.tiles[plane.y][plane.x];
	if (!cub->minimap.corners[TOPRIGHT]->right)
		cub->minimap.corners[TOPLEFT] = &cub->minimap.tiles[plane.y0][plane.x
			- 10];
	if (!cub->minimap.corners[BOTTLEFT]->down)
		cub->minimap.corners[TOPLEFT] = &cub->minimap.tiles[plane.y
			- 10][plane.x0];
	if (!cub->minimap.corners[BOTTRIGHT]->right)
		cub->minimap.corners[TOPLEFT] = &cub->minimap.tiles[cub->minimap.corners[TOPLEFT]->crd.y][plane.x
			- 10];
}
