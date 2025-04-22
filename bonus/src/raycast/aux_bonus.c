/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcsilv <marcsilv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:22:29 by efinda            #+#    #+#             */
/*   Updated: 2025/04/16 21:08:07 by marcsilv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

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
		|| tile_x > cub->scene.map.size.x - 1 || cub->minimap.tiles[tile_y][tile_x].id == '1')
		return (1);
	else if (tile_y < 0 || tile_y > cub->scene.map.size.y - 1 || tile_x < 0
		|| tile_x > cub->scene.map.size.x - 1 || cub->minimap.tiles[tile_y][tile_x].id == 'D')
		return (2);
	return (cub->minimap.tiles[tile_y][tile_x].id == 'D');
}

inline int	face_down(double angle)
{
	return ((angle > 0 && angle < M_PI));
}

inline int	face_right(double angle)
{
	return ((angle < M_PI_2 || angle > (3 * M_PI_2)));
}

inline t_texture	*get_texture(t_cub *cub, double angle, t_point dir, int j)
{
	if (cub->rays[j].hor.is_door || cub->rays[j].ver.is_door)
		return (&cub->scene.door);
	if (!face_down(angle) && dir.x && !dir.y)
		return (&cub->scene.textures[NO]);
	if (face_down(angle) && dir.x && !dir.y)
		return (&cub->scene.textures[SO]);
	if (face_right(angle) && dir.y && !dir.x)
		return (&cub->scene.textures[EA]);
	if (!face_right(angle) && dir.y && !dir.x)
		return (&cub->scene.textures[WE]);
	return (NULL);
}
