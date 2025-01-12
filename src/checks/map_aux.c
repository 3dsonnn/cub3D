/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_aux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 02:12:28 by efinda            #+#    #+#             */
/*   Updated: 2025/01/12 05:39:47 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	free_visited(t_map *map)
{
	int	i;

	i = -1;
	while (++i < map->size.y)
		free(map->visited[i]);
	free(map->visited);
}

static bool	is_on_border(t_map *map)
{
	return (map->neighbor.x == 0 || map->neighbor.x == map->size.x - 1
		|| map->neighbor.y == 0 || map->neighbor.y == map->size.y - 1);
}

static bool	has_space_nearby(t_map *map, t_point pos)
{
	int	d;

	d = -1;
	while (++d < 4)
	{
		map->nx = pos.x + map->dx[d];
		map->ny = pos.y + map->dy[d];
		if (map->nx >= 0 && map->nx < map->size.x && map->ny >= 0
			&& map->ny < map->size.y)
			if (map->content[map->ny][map->nx] == ' ')
				return (true);
	}
	return (false);
}

static void	my_flood_fill_aux(t_map *map, t_point *stack, int *top)
{
	int	d;

	d = -1;
	while (++d < 4)
	{
		map->nx = map->cur.x + map->dx[d];
		map->ny = map->cur.y + map->dy[d];
		if (map->nx >= 0 && map->nx < map->size.x && map->ny >= 0
			&& map->ny < map->size.y && !map->visited[map->ny][map->nx]
			&& map->content[map->ny][map->nx] == '1')
		{
			map->neighbor = (t_point){map->nx, map->ny};
			if (is_on_border(map) || has_space_nearby(map, map->neighbor))
			{
				stack[++(*top)] = map->neighbor;
				map->visited[map->ny][map->nx] = true;
			}
		}
	}
}

bool	my_flood_fill(t_map *map)
{
	int		top;
	t_point	stack[map->size.x * map->size.y];

	top = -1;
	stack[++top] = map->init;
	map->visited[map->init.y][map->init.x] = true;
	while (top >= 0)
	{
		map->cur = stack[top--];
		if (map->cur.x == map->init.x && map->cur.y == map->init.y && top != -1)
		{
			free_visited(map);
			return (true);
		}
		my_flood_fill_aux(map, stack, &top);
	}
	free_visited(map);
	return (false);
}
