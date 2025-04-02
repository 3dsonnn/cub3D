/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 01:25:03 by efinda            #+#    #+#             */
/*   Updated: 2025/04/02 00:46:19 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static void	update_cur_tile(t_cub *cub, double x, double y)
{
	int	i;
	int	j;

	i = (int)floor(y / TILE);
	j = (int)floor(x / TILE);
	cub->minimap.cur->id = '0';
	cub->minimap.cur = &cub->minimap.tiles[i][j];
	cub->minimap.cur->id = 'C';
	update_obx(cub, cub->minimap.corners, cub->minimap.tiles);
}

static int	obx_overlaps_wall(t_dpoint pos, t_point check)
{
	t_plane	wall;
	t_plane	player;

	wall.x0 = check.x * TILE;
	wall.x = wall.x0 + TILE;
	wall.y0 = check.y * TILE;
	wall.y = wall.y0 + TILE;
	player.x0 = pos.x - PLAYER_RADIUS;
	player.x = pos.x + PLAYER_RADIUS;
	player.y0 = pos.y - PLAYER_RADIUS;
	player.y = pos.y + PLAYER_RADIUS;
	if (player.x > wall.x0 && player.x0 < wall.x && player.y > wall.y0
		&& player.y0 < wall.y)
		return (1);
	return (0);
}

static int	player_is_wall(t_cub *cub, t_dpoint pos, t_point offsets[4], int i)
{
	t_point	tile;
	t_point	check;

	tile = (t_point){(int)(pos.x / TILE), (int)(pos.y / TILE)};
	while (++i < 4)
	{
		check.x = tile.x + offsets[i].x;
		check.y = tile.y + offsets[i].y;
		if (check.x < 0 || check.x >= cub->scene.map.size.x || check.y < 0
			|| check.y >= cub->scene.map.size.y)
			return (1);
		if (cub->minimap.tiles[check.y][check.x].id == '1'
			&& obx_overlaps_wall(pos, check))
			return (1);
	}
	return (0);
}

static int	move(t_cub *cub, t_dpoint vector, int direction, t_dpoint new_pos)
{
	new_pos.x += vector.x * (SPEED + PLAYER_RADIUS) * direction;
	new_pos.y += vector.y * (SPEED + PLAYER_RADIUS) * direction;
	if (player_is_wall(cub, new_pos, (t_point[]){{0, 0}, {1, 0}, {0, 1}, {1,
			1}}, -1))
		return (1);
	cub->player.pos.x += vector.x * SPEED * direction;
	cub->player.pos.y += vector.y * SPEED * direction;
	if (cub->minimap.cur != &cub->minimap.tiles[(int)floor(cub->player.pos.y
			/ TILE)][(int)floor(cub->player.pos.x / TILE)])
		update_cur_tile(cub, cub->player.pos.x, cub->player.pos.y);
	return (0);
}

int	move_player(t_cub *cub, int keycode)
{
	if (keycode == WKEY)
		return (move(cub, cub->player.dir, 1, cub->player.pos));
	if (keycode == SKEY)
		return (move(cub, cub->player.dir, -1, cub->player.pos));
	if (keycode == DKEY)
		return (move(cub, cub->player.plane, 1, cub->player.pos));
	if (keycode == AKEY)
		return (move(cub, cub->player.plane, -1, cub->player.pos));
	return (1);
}
