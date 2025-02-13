/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:22:29 by efinda            #+#    #+#             */
/*   Updated: 2025/02/10 11:28:10 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

int inside_map(t_cub *cub, double x, double y)
{
	if (x >= 0 && x < cub->scene.map.size.x * TILE_SIZE && \
		y >= 0 && y < cub->scene.map.size.y * TILE_SIZE)
		return (1);
	return (0);
}

int is_wall(t_cub *cub, double x, double y)
{
	int	tile_x;
	int	tile_y;

	if (x < 0 || x >= cub->scene.map.size.x * TILE_SIZE || \
		y < 0 || y >= cub->scene.map.size.y * TILE_SIZE)
		return (1);
	tile_x = (int)floor(x / TILE_SIZE);
	tile_y = (int)floor(y / TILE_SIZE);
	return (cub->scene.map[tile_y][tile_x] == '1');
}