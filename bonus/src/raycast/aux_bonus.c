/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:22:29 by efinda            #+#    #+#             */
/*   Updated: 2025/04/25 20:01:10 by efinda           ###   ########.fr       */
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
	if (tile_x < 0 || tile_x > cub->scene.map.size.x - 1 || tile_y < 0
		|| tile_y > cub->scene.map.size.y - 1 || cub->minimap.tiles[tile_y][tile_x].id == '1')
		return (1);
	if (cub->minimap.tiles[tile_y][tile_x].id == 'D')
		return (2);
	return (0);
}

inline int	face_down(double angle)
{
	return ((angle > 0 && angle < M_PI));
}

inline int	face_right(double angle)
{
	return ((angle < M_PI_2 || angle > (3 * M_PI_2)));
}

void	get_texture(t_cub *cub, t_ray *ray, double angle, t_point dir)
{
	if (ray->hor.is_door || ray->ver.is_door)
		ray->img = cub->scene.map.door.door;
	else if (!face_down(angle) && dir.x)
		ray->img = cub->scene.textures[NO].img;
	else if (face_down(angle) && dir.x)
		ray->img = cub->scene.textures[SO].img;
	else if (face_right(angle) && dir.y)
		ray->img = cub->scene.textures[EA].img;
	else if (!face_right(angle) && dir.y)
		ray->img = cub->scene.textures[WE].img;
}
