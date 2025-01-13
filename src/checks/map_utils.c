/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 19:27:48 by efinda            #+#    #+#             */
/*   Updated: 2025/01/13 09:14:43 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	check_empty_spaces(t_scene *scene, t_map *map)
{
	int	p[3];

	ft_memset(p, -1, 3 * sizeof(int));
	if (ft_strchr(*map->content, '0') || ft_strchr(map->content[map->size.y
			- 1], '0'))
		exit_error("Invalid map: not surrounded by walls", scene);
	while (++(*p) < map->size.y)
		if (*map->content[*p] == '0' || map->content[*p][map->size.x
			- 1] == '0')
			exit_error("Invalid map: not surrounded by walls", scene);
	while (++(p[1]) < map->size.y)
	{
		p[2] = -1;
		while (++(p[2]) < map->size.x)
			if (map->content[p[1]][p[2]] == '0')
				if (map->content[p[1] + 1][p[2]] == ' ' || map->content[p[1]
					- 1][p[2]] == ' ' || map->content[p[1]][p[2] + 1] == ' '
					|| map->content[p[1]][p[2] - 1] == ' ' || map->content[p[1]
					- 1][p[2] - 1] == ' ' || map->content[p[1] - 1][p[2]
					+ 1] == ' ' || map->content[p[1] + 1][p[2] - 1] == ' '
					|| map->content[p[1] + 1][p[2] + 1] == ' ')
					exit_error("Invalid map: a 0 cannot be surrounded by a space",
						scene);
	}
}

static void	check_start_pos(t_scene *scene, t_map *map)
{
	int	p[3];

	ft_memset(p, -1, 3 * sizeof(int));
	if (ft_strchr(*map->content, map->start)
		|| ft_strchr(map->content[map->size.y - 1], map->start))
		exit_error("Invalid map: not surrounded by walls", scene);
	while (++(*p) < map->size.y)
		if (*map->content[*p] == map->start || map->content[*p][map->size.x
			- 1] == map->start)
			exit_error("Invalid map: not surrounded by walls", scene);
	while (++(p[1]) < map->size.y)
	{
		p[2] = -1;
		while (++(p[2]) < map->size.x)
			if (map->content[p[1]][p[2]] == map->start)
				if (map->content[p[1] + 1][p[2]] == ' ' || map->content[p[1]
					- 1][p[2]] == ' ' || map->content[p[1]][p[2] + 1] == ' '
					|| map->content[p[1]][p[2] - 1] == ' ' || map->content[p[1]
					+ 1][p[2] + 1] == ' ' || map->content[p[1] + 1][p[2]
					- 1] == ' ' || map->content[p[1] - 1][p[2] + 1] == ' '
					|| map->content[p[1] - 1][p[2] - 1] == ' ')
					exit_error("Invalid map: the start position cannot be surrounded by a space",
						scene);
	}
}

static void	check_spaces(t_scene *scene, t_map *map, int x, int y)
{
	while (++y < map->size.y)
	{
		x = -1;
		while (++x < map->size.x)
		{
			if (map->content[y][x] == ' ')
			{
				if ((y > 0 && !ft_strchr(" 1", map->content[y - 1][x]))
					|| (y < map->size.y - 1 && !ft_strchr(" 1", map->content[y
							+ 1][x])) || (x > 0 && !ft_strchr(" 1",
							map->content[y][x - 1])) || (x < map->size.x - 1
						&& !ft_strchr(" 1", map->content[y][x + 1])) || (y > 0
						&& x > 0 && !ft_strchr(" 1", map->content[y - 1][x
							- 1])) || (y > 0 && x < map->size.x - 1
						&& !ft_strchr(" 1", map->content[y - 1][x + 1]))
					|| (y < map->size.y - 1 && x > 0 && !ft_strchr(" 1",
							map->content[y + 1][x - 1])) || (y < map->size.y - 1
						&& x < map->size.x - 1 && !ft_strchr(" 1",
							map->content[y + 1][x + 1])))
					exit_error("Invalid map: a space can only be surrounded another space or a wall",
						scene);
			}
		}
	}
}

void	is_surrounded(t_scene *scene, t_map *map, int y)
{
	check_empty_spaces(scene, map);
	check_start_pos(scene, map);
	check_spaces(scene, map, -1, -1);
	ft_replace_char(*map->content, '1', '*');
	ft_replace_char(map->content[map->size.y - 1], '1', '*');
	while (++y < map->size.y)
	{
		if (*map->content[y] == '1')
			*map->content[y] = '*';
		if (map->content[y][map->size.x - 1] == '1')
			map->content[y][map->size.x - 1] = '*';
	}
	my_flood_fill(map, -1, -1);
	// flood_fill(map->content, map->size, map->start);
}
