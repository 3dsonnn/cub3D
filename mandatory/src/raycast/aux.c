/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:22:29 by efinda            #+#    #+#             */
/*   Updated: 2025/03/06 05:08:18 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

int	inside_map(t_cub *cub, double x, double y)
{
	if (x >= 0 && x < cub->scene.map.size.x * TILE && y >= 0
		&& y < cub->scene.map.size.y * TILE)
		return (1);
	return (0);
}

int	is_wall(t_cub *cub, double x, double y)
{
	int tile_x;
	int tile_y;

	if (x < 0 || x >= cub->scene.map.size.x * TILE || y < 0
		|| y >= cub->scene.map.size.y * TILE)
		return (1);
	tile_x = (int)floor(x / TILE);
	tile_y = (int)floor(y / TILE);
	if (tile_y < 0 || tile_y > cub->scene.map.size.y - 1 || tile_x < 0
		|| tile_x > cub->scene.map.size.x - 1 || cub->scene.map.content[tile_y][tile_x] == '1')
		return (1);
	return (cub->scene.map.content[tile_y][tile_x] == '1');
}

inline	t_texture   *get_texture(t_cub *cub, double angle, t_point dir)
{
    if (FACE_UP(angle) && dir.x && !dir.y)
        return (&cub->scene.textures[NO]);
    if (FACE_DOWN(angle) && dir.x && !dir.y)
        return (&cub->scene.textures[SO]);
    if (FACE_RIGHT(angle) && dir.y && !dir.x)
        return (&cub->scene.textures[EA]);
    if (FACE_LEFT(angle) && dir.y && !dir.x)
        return (&cub->scene.textures[WE]);
	return (NULL);
}
