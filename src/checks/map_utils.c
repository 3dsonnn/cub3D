/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 19:27:48 by efinda            #+#    #+#             */
/*   Updated: 2025/01/12 01:25:30 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	check_empty_spaces(t_scene *scene, t_map *map)
{
	int	p[4];

	ft_memset(p, -1, 4 * sizeof(int));
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
					|| map->content[p[1]][p[2] - 1] == ' ')
					p[3] = 1;
	}
	if (p[3] == 1)
		exit_error("Invalid map: a 0 cannot touch a space", scene);
}

static void	check_start_pos(t_scene *scene, t_map *map)
{
	int	p[4];

	ft_memset(p, -1, 4 * sizeof(int));
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
					|| map->content[p[1]][p[2] - 1] == ' ')
					p[3] = 1;
	}
	if (p[3] == 1)
		exit_error("Invalid map: the start position cannot touch a space",
			scene);
}

static void	check_spaces(t_scene *scene, t_map *map)
{
	int	p[3];

	ft_memset(p, -1, 4 * sizeof(int));
	while (++(*p) < map->size.y)
	{
		p[1] = -1;
		while (++(p[1]) < map->size.x)
			if (map->content[*p][p[1]] == ' ')
				if ((*p > 0 && map->content[*p - 1][p[1]] != 1
						&& map->content[*p - 1][p[1]] != ' ')
					|| (*p < map->size.y - 1 && map->content[*p + 1][p[1]] != 1
						&& map->content[*p + 1][p[1]] != ' ') || (p[1] > 0
						&& map->content[*p][p[1] - 1] != 1
						&& map->content[*p][p[1] - 1] != ' ')
					|| (p[1] < map->size.x - 1 && map->content[*p][p[1]
						- 1] != 1 && map->content[*p][p[1] - 1] != ' '))
					p[2] = 1;
	}
	if (p[2] == 1)
		exit_error("Invalid map: a space can only touch another space or a wall",
			scene);
}

static void	check_walls(t_scene *scene, t_map *map)
{
	int	p[3];

	ft_memset(p, -1, 4 * sizeof(int));
	while (++(*p) < map->size.y)
	{
		p[1] = -1;
		while (++(p[1]) < map->size.x)
			if (map->content[*p][p[1]] == ' ')
				if ((*p > 0 && map->content[*p - 1][p[1]] != 1
						&& map->content[*p - 1][p[1]] != ' ')
					|| (*p < map->size.y - 1 && map->content[*p + 1][p[1]] != 1
						&& map->content[*p + 1][p[1]] != ' ') || (p[1] > 0
						&& map->content[*p][p[1] - 1] != 1
						&& map->content[*p][p[1] - 1] != ' ')
					|| (p[1] < map->size.x - 1 && map->content[*p][p[1]
						- 1] != 1 && map->content[*p][p[1] - 1] != ' '))
					p[2] = 1;
	}
	if (p[2] == 1)
		exit_error("Invalid map: a space can only touch another space or a wall",
			scene);
}

void	is_surrounded(t_scene *scene, t_map *map)
{
	check_empty_spaces(scene, map);
	check_start_pos(scene, map);
	check_spaces(scene, map);
	check_walls(scene, map);
}
