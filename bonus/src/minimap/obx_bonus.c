/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obx_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 22:51:48 by efinda            #+#    #+#             */
/*   Updated: 2025/03/06 00:17:20 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

void    update_obx(t_cub *cub, t_tile *cur, t_plane plane, t_iter iter)
{
    if (!cub->minimap.box)
        return ;
    t_tile	*tmp[4] = {cur, cur, cur, cur};

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

    plane.x0 = tmp[2]->crd.x;
    plane.x = tmp[3]->crd.x;
    plane.y0 = tmp[0]->crd.y;
    plane.y = tmp[1]->crd.y;

    cub->minimap.corners[TOPLEFT] = &cub->minimap.tiles[plane.y0][plane.x0];
    cub->minimap.corners[TOPRIGHT] = &cub->minimap.tiles[plane.y0][plane.x];
    cub->minimap.corners[BOTTLEFT] = &cub->minimap.tiles[plane.y][plane.x0];
    cub->minimap.corners[BOTTRIGHT] = &cub->minimap.tiles[plane.y][plane.x];

    if (!cub->minimap.corners[TOPRIGHT]->right)
        cub->minimap.corners[TOPLEFT] = &cub->minimap.tiles[plane.y0][plane.x - 10];

    if (!cub->minimap.corners[BOTTLEFT]->down)
		cub->minimap.corners[TOPLEFT] = &cub->minimap.tiles[plane.y - 10][plane.x0];
    
    if (!cub->minimap.corners[BOTTRIGHT]->right)
		cub->minimap.corners[TOPLEFT] = &cub->minimap.tiles[cub->minimap.corners[TOPLEFT]->crd.y][plane.x - 10];
}
