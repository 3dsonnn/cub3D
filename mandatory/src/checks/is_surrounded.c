/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_surrounded.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:26:25 by efinda            #+#    #+#             */
/*   Updated: 2025/04/23 18:00:29 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	check_boundary_columns(t_scene *scene, t_map *map, t_row *head)
{
	while (head)
	{
		if (*head->str == '0')
		{
			add_map_crd(&map->crds, new_map_crd('0', ft_itoa(0), head->line_nbr));
			scene->tmp = map_crds_to_str(map->crds, "Invalid map: not surrounded by walls due to:");
			exit_error(scene->tmp, scene);
		}
		if (head->str[map->size.x - 1] == '0')
		{
			add_map_crd(&map->crds, new_map_crd('0', ft_itoa(map->size.x - 1), head->line_nbr));
			scene->tmp = map_crds_to_str(map->crds, "Invalid map: not surrounded by walls due to:");
			exit_error(scene->tmp, scene);
		}
		if (*head->str == map->start)
		{
			add_map_crd(&map->crds, new_map_crd(map->start, ft_itoa(0), head->line_nbr));
			scene->tmp = map_crds_to_str(map->crds, "Invalid map: not surrounded by walls due to:");
			exit_error(scene->tmp, scene);
		}
		if (head->str[map->size.x - 1] == map->start)
		{
			add_map_crd(&map->crds, new_map_crd(map->start, ft_itoa(map->size.x - 1), head->line_nbr));
			scene->tmp = map_crds_to_str(map->crds, "Invalid map: not surrounded by walls due to:");
			exit_error(scene->tmp, scene);
		}
		head = head->next;
	}
}

static void	check_boundary_lines(t_scene *scene, t_map *map, t_row *head, t_row *tail)
{
	if (ft_strchr(head->str, '0'))
	{
		add_map_crd(&map->crds, new_map_crd('0', ft_itoa(ft_strchr(head->str, '0') - head->str), head->line_nbr));
		scene->tmp = map_crds_to_str(map->crds, "Invalid map: not surrounded by walls due to:");
		exit_error(scene->tmp, scene);
	}
	if (ft_strchr(tail->str, '0'))
	{
		add_map_crd(&map->crds, new_map_crd('0', ft_itoa(ft_strchr(tail->str, '0') - tail->str), tail->line_nbr));
		scene->tmp = map_crds_to_str(map->crds, "Invalid map: not surrounded by walls due to:");
		exit_error(scene->tmp, scene);
	}
	if (ft_strchr(head->str, map->start))
	{
		add_map_crd(&map->crds, new_map_crd(map->start, ft_itoa(ft_strchr(head->str, map->start) - head->str), head->line_nbr));
		scene->tmp = map_crds_to_str(map->crds, "Invalid map: not surrounded by walls due to:");
		exit_error(scene->tmp, scene);
	}
	if (ft_strchr(tail->str, map->start))
	{
		add_map_crd(&map->crds, new_map_crd(map->start, ft_itoa(ft_strchr(tail->str, map->start) - tail->str), tail->line_nbr));
		scene->tmp = map_crds_to_str(map->crds, "Invalid map: not surrounded by walls due to:");
		exit_error(scene->tmp, scene);
	}
	check_boundary_columns(scene, map, head);
}

static inline int	is_surrounded_aux(t_row *cur, int i)
{
	if (cur->str[i + 1] == ' ' || cur->str[i - 1] == ' '
		|| cur->prev->str[i] == ' ' || cur->next->str[i] == ' ')
		return (1);
	return (0);
}

void	is_surrounded(t_scene *scene, t_map *map, t_row *head, t_row *tile)
{
	int	i;

	check_boundary_lines(scene, map, head->prev, tile);
	while (head != tile->prev)
	{
		i = 0;
		while (++i < map->size.x - 1)
		{
			if ((head->str[i] == '0' || head->str[i] == map->start)
				&& is_surrounded_aux(head, i))
			{
				add_map_crd(&map->crds, new_map_crd(head->str[i], ft_itoa(i), head->line_nbr));
				scene->tmp = map_crds_to_str(map->crds, "Invalid map: not surrounded by walls due to:");
				exit_error(scene->tmp, scene);
			}
		}
		head = head->next;
	}
}
