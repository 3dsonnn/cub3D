/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_surrounded.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:26:25 by efinda            #+#    #+#             */
/*   Updated: 2025/03/16 10:45:20 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	check_boundary_columns(t_scene *scene, t_map *map, int i)
{
	while (++i < map->size.y)
	{
		if (*map->content[i] == '0')
			exit_error("Invalid map: not surrounded by walls due to a 0 on the first column",
				scene);
		if (map->content[i][map->size.x - 1] == '0')
			exit_error("Invalid map: not surrounded by walls due to a 0 on the last column",
				scene);
		if (*map->content[i] == map->start)
			exit_error("Invalid map: the start position cannot be on the first column",
				scene);
		if (map->content[i][map->size.x - 1] == map->start)
			exit_error("Invalid map: the start position cannot be on the last column",
				scene);
	}
}

static void	check_boundary_lines(t_scene *scene, t_map *map)
{
	if (ft_strchr(*map->content, '0'))
		exit_error("Invalid map: not surrounded by walls due to a 0 on the first line",
			scene);
	if (ft_strchr(map->content[map->size.y - 1], '0'))
		exit_error("Invalid map: not surrounded by walls due to a 0 on the last line",
			scene);
	if (ft_strchr(*map->content, map->start))
		exit_error("Invalid map: the start position cannot be on the first line",
			scene);
	if (ft_strchr(map->content[map->size.y - 1], map->start))
		exit_error("Invalid map: the start position cannot be on the last line",
			scene);
	check_boundary_columns(scene, map, -1);
}

static inline int	is_surrounded_aux(char **mtx, int i, int j)
{
	if (mtx[i + 1][j] == ' ' || mtx[i - 1][j] == ' ' || mtx[i][j + 1] == ' '
		|| mtx[i][j - 1] == ' ')
		return (1);
	return (0);
}

void	is_surrounded(t_scene *scene, t_map *map, t_point iter)
{
	check_boundary_lines(scene, map);
	while (++iter.y < map->size.y - 1)
	{
		iter.x = 0;
		while (++iter.x < map->size.x - 1)
		{
			if (map->content[iter.y][iter.x] == '0' && is_surrounded_aux(map->content, iter.y,
					iter.x))
				exit_error("Invalid map: a 0 cannot be surrounded by a space",
					scene);
			if (map->content[iter.y][iter.x] == map->start && is_surrounded_aux(map->content,
					iter.y, iter.x))
				exit_error("Invalid map: the start position cannot be surrounded by a space",
					scene);
		}
	}
	map->content[map->spos.y][map->spos.x] = '0';
}
