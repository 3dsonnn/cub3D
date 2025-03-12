/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obx_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 22:51:48 by efinda            #+#    #+#             */
/*   Updated: 2025/03/12 19:52:18 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static  void    edge_cases(t_cub *cub, t_plane plane)
{
    if (plane.x - 10 > 0)
    {
        if (!cub->minimap.corners[TOPRIGHT]->right)
            cub->minimap.corners[TOPLEFT] = &cub->minimap.tiles[plane.y0][plane.x - 10];
        if (!cub->minimap.corners[BOTTRIGHT]->right)
		    cub->minimap.corners[TOPLEFT] = &cub->minimap.tiles[cub->minimap.corners[TOPLEFT]->crd.y][plane.x - 10];
    }
    if (!cub->minimap.corners[BOTTLEFT]->down && (plane.y - 10) > 0)
		cub->minimap.corners[TOPLEFT] = &cub->minimap.tiles[plane.y - 10][plane.x0];
}

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
    edge_cases(cub, plane);
}

// void update_obx(t_cub *cub, t_tile *cur, t_plane plane, t_iter iter)
// {
//     if (!cub->minimap.box || !cur)
//         return;

//     t_tile *tmp[4] = {cur, cur, cur, cur};
//     const int VIEW_RANGE = 20;  // Configurable view distance

//     // Navigate directions with bounds checking
//     while (++(iter.i) < VIEW_RANGE && cur && cur->up)
//         tmp[0] = cur = cur->up;
//     cur = cub->minimap.cur;
//     while (++(iter.j) < VIEW_RANGE && cur && cur->down)
//         tmp[1] = cur = cur->down;
//     cur = cub->minimap.cur;
//     while (++(iter.k) < VIEW_RANGE && cur && cur->left)
//         tmp[2] = cur = cur->left;
//     cur = cub->minimap.cur;
//     while (++(iter.l) < VIEW_RANGE && cur && cur->right)
//         tmp[3] = cur = cur->right;

//     // Set boundaries
//     plane.x0 = tmp[2]->crd.x;
//     plane.x = tmp[3]->crd.x;
//     plane.y0 = tmp[0]->crd.y;
//     plane.y = tmp[1]->crd.y;

//     // Assign corners with bounds checking
//     if (plane.y0 >= 0 && plane.x0 >= 0 && plane.y < cub->scene.map.size.y && plane.x < cub->scene.map.size.x)
//     {
//         cub->minimap.corners[TOPLEFT] = &cub->minimap.tiles[plane.y0][plane.x0];
//         cub->minimap.corners[TOPRIGHT] = &cub->minimap.tiles[plane.y0][plane.x];
//         cub->minimap.corners[BOTTLEFT] = &cub->minimap.tiles[plane.y][plane.x0];
//         cub->minimap.corners[BOTTRIGHT] = &cub->minimap.tiles[plane.y][plane.x];
//     }

//     const int EDGE_OFFSET = 10;
//     // Adjust corners independently
//     if (!cub->minimap.corners[TOPRIGHT]->right && plane.x > EDGE_OFFSET)
//         cub->minimap.corners[TOPRIGHT] = &cub->minimap.tiles[plane.y0][plane.x - EDGE_OFFSET];
    
//     if (!cub->minimap.corners[BOTTLEFT]->down && plane.y > EDGE_OFFSET)
//         cub->minimap.corners[BOTTLEFT] = &cub->minimap.tiles[plane.y - EDGE_OFFSET][plane.x0];
// }
