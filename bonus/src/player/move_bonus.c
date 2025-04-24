/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcsilv <marcsilv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 01:25:03 by efinda            #+#    #+#             */
/*   Updated: 2025/04/24 14:35:37 by marcsilv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static void	update_cur_tile(t_cub *cub, double x, double y)
{
	int	i;
	int	j;

	i = (int)floor(y / TILE);
	j = (int)floor(x / TILE);
	if (cub->minimap.cur->id != 'D' && cub->minimap.cur->id != 'd')
		cub->minimap.cur->id = '0';
	cub->minimap.cur = &cub->minimap.tiles[i][j];
	// cub->minimap.cur->id = 'C';
	update_obx(cub);
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
		if ((cub->minimap.tiles[check.y][check.x].id == '1'
			|| cub->minimap.tiles[check.y][check.x].id == 'D')
			&& obx_overlaps_wall(pos, check))
			return (1);
	}
	return (0);
}

void	move_player(t_cub *cub, double forward, double strafe, t_dpoint new_pos)
{
	if (forward)
	{
		new_pos.x += cub->player.dir.x * (SPEED + PLAYER_RADIUS) * forward;
		new_pos.y += cub->player.dir.y * (SPEED + PLAYER_RADIUS) * forward;
		if (!player_is_wall(cub, new_pos, (t_point[]){{0, 0}, {1, 0}, {0, 1},
				{1, 1}}, -1))
		{
			cub->player.pos.x += cub->player.dir.x * SPEED * forward;
			cub->player.pos.y += cub->player.dir.y * SPEED * forward;
		}
	}
	if (strafe)
	{
		new_pos.x += cub->player.plane.x * (SPEED + PLAYER_RADIUS) * strafe;
		new_pos.y += cub->player.plane.y * (SPEED + PLAYER_RADIUS) * strafe;
		if (!player_is_wall(cub, new_pos, (t_point[]){{0, 0}, {1, 0}, {0, 1},
				{1, 1}}, -1))
		{
			cub->player.pos.x += cub->player.plane.x * SPEED * strafe;
			cub->player.pos.y += cub->player.plane.y * SPEED * strafe;
		}
	}
	if (cub->minimap.cur != &cub->minimap.tiles[(int)floor(cub->player.pos.y
			/ TILE)][(int)floor(cub->player.pos.x / TILE)])
		update_cur_tile(cub, cub->player.pos.x, cub->player.pos.y);
}

void	rotate_player(t_cub *cub, double angle_delta)
{
	cub->player.angle += angle_delta;
	cub->player.angle = ft_normalizer(cub->player.angle);
	cub->player.dir.x = cos(cub->player.angle);
	cub->player.dir.y = sin(cub->player.angle);
	cub->player.plane.x = -cub->player.dir.y;
	cub->player.plane.y = cub->player.dir.x;
	rotate_image(cub->scene.e_key.img, &cub->scene.rotated_key.img, cub->player.angle, cub);
}
