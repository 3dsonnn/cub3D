/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_surrounded.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:26:25 by efinda            #+#    #+#             */
/*   Updated: 2025/04/21 21:30:36 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	check_boundary_lines(t_scene *scene, t_map *map, int i)
{
	if (ft_strchr(*map->content, '0')
		|| ft_strchr(map->content[map->size.y - 1], '0')
		|| ft_strchr(*map->content, map->start)
		|| ft_strchr(map->content[map->size.y - 1], map->start))
		exit_error("Invalid map: not surrounded by walls",
			scene);
	while (++i < map->size.y)
	{
		if (*map->content[i] == '0'
			|| map->content[i][map->size.x - 1] == '0'
			|| *map->content[i] == map->start
			|| map->content[i][map->size.x - 1] == map->start)
			exit_error("Invalid map: not surrounded by walls",
				scene);
	}
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
	check_boundary_lines(scene, map, -1);
	while (++iter.y < map->size.y - 1)
	{
		iter.x = 0;
		while (++iter.x < map->size.x - 1)
		{
			if ((map->content[iter.y][iter.x] == '0'
				&& is_surrounded_aux(map->content, iter.y, iter.x))
				|| (map->content[iter.y][iter.x] == map->start
				&& is_surrounded_aux(map->content, iter.y, iter.x)))
			{
				ft_printf("%d...\n", scene->line_nbr.value + iter.y);
				exit_error("Invalid map: not surrounded by walls",
					scene);
			}
		}
	}
	map->content[map->spos.y][map->spos.x] = '0';
}
