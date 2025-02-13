/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 01:25:12 by efinda            #+#    #+#             */
/*   Updated: 2025/02/10 15:13:53 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

inline int	same_tile(t_cub *cub, t_tile *tile, int x, int y)
{
	t_plane	pos;

	pos.x0 = cub->minimap.tilesize * tile->crd.x;
	pos.x = pos.x0 + cub->minimap.tilesize;
	pos.y0 = cub->minimap.tilesize * tile->crd.y;
	pos.y = pos.y0 + cub->minimap.tilesize;
	return (x >= pos.x0 && x < pos.x && y >= pos.y0 && y < pos.y);
}

inline void	update_neighbors(t_cub *cub)
{
	cub->player.neighbors[0] = cub->cur->up;
	cub->player.neighbors[1] = cub->cur->upleft;
	cub->player.neighbors[2] = cub->cur->upright;
	cub->player.neighbors[3] = cub->cur->down;
	cub->player.neighbors[4] = cub->cur->downleft;
	cub->player.neighbors[5] = cub->cur->downright;
	cub->player.neighbors[6] = cub->cur->left;
	cub->player.neighbors[7] = cub->cur->right;
}
