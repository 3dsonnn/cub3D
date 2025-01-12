/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_aux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 02:12:28 by efinda            #+#    #+#             */
/*   Updated: 2025/01/12 19:14:31 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static	void	fill_diagonal(t_map *map, int x, int y)
{
	while (++y < map->size.y - 1)
	{
		x = -1;
		while (++x < map->size.x - 1)
		{
			if (map->content[y][x] == ' ')
			{
				if (y > 0 && x > 0 && map->content[y - 1][x - 1] == '1')
					map->content[y - 1][x - 1] = '*';
				if (y > 0 && x < map->size.x - 1 && map->content[y - 1][x
					+ 1] == '1')
					map->content[y - 1][x + 1] = '*';
				if (y < map->size.y - 1 && x > 0 && map->content[y + 1][x
					- 1] == '1')
					map->content[y + 1][x - 1] = '*';
				if (y < map->size.y - 1 && x < map->size.x - 1 && map->content[y
					+ 1][x + 1] == '1')
					map->content[y + 1][x + 1] = '*';
			}
		}
	}
}

void	my_flood_fill(t_map *map, int x, int y)
{
	while (++y < map->size.y - 1)
	{
		x = -1;
		while (++x < map->size.x - 1)
		{
			if (map->content[y][x] == ' ')
			{
				if (y > 0 && map->content[y - 1][x] == '1')
					map->content[y - 1][x] = '*';
				if (y < map->size.y - 1 && map->content[y + 1][x] == '1')
					map->content[y + 1][x] = '*';
				if (x > 0 && map->content[y][x - 1] == '1')
					map->content[y][x - 1] = '*';
				if (x < map->size.x - 1 && map->content[y][x + 1] == '1')
					map->content[y][x + 1] = '*';
			}
		}
	}
	fill_diagonal(map, -1, -1);
}

