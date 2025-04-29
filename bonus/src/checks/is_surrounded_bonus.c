/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_surrounded_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 22:26:25 by efinda            #+#    #+#             */
/*   Updated: 2025/04/28 19:44:08 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static void	check_boundary_columns(t_scene *scene, t_map *map, t_row *head,
		char c)
{
	while (head)
	{
		if (*head->str == '0' || head->str[map->size.x - 1] == '0')
			c = '0';
		else if (*head->str == 'D' || head->str[map->size.x - 1] == 'D')
			c = 'D';
		else if (*head->str == map->start || head->str[map->size.x
			- 1] == map->start)
			c = map->start;
		else
		{
			head = head->next;
			continue ;
		}
		map_crd_error_message(scene,
			"Invalid map: not surrounded by walls due to:", c,
			(t_nbr){.str = ft_strdup(head->line_nbr),
			.value = ft_strchr(head->str, c) - head->str});
		exit_error(scene->tmp, scene);
		head = head->next;
	}
}

static void	check_tail_line(t_scene *scene, t_map *map, t_row *tail)
{
	char	c;

	if (ft_strchr(tail->str, '0'))
		c = '0';
	else if (ft_strchr(tail->str, 'D'))
		c = 'D';
	else if (ft_strchr(tail->str, map->start))
		c = map->start;
	else
		return ;
	map_crd_error_message(scene, "Invalid map: not surrounded by walls due to:",
		c, (t_nbr){.str = ft_strdup(tail->line_nbr),
		.value = ft_strchr(tail->str, c) - tail->str});
	exit_error(scene->tmp, scene);
}

static void	check_head_line(t_scene *scene, t_map *map, t_row *head)
{
	char	c;

	if (ft_strchr(head->str, '0'))
		c = '0';
	else if (ft_strchr(head->str, 'D'))
		c = 'D';
	else if (ft_strchr(head->str, map->start))
		c = map->start;
	else
		return ;
	map_crd_error_message(scene, "Invalid map: not surrounded by walls due to:",
		c, (t_nbr){.str = ft_strdup(head->line_nbr),
		.value = ft_strchr(head->str, c) - head->str});
	exit_error(scene->tmp, scene);
}

void	is_surrounded(t_scene *scene, t_map *map, t_row *head, t_row *tail)
{
	int	i;

	check_head_line(scene, map, head->prev);
	check_tail_line(scene, map, tail);
	check_boundary_columns(scene, map, head, '\0');
	while (head != tail)
	{
		i = 0;
		while (++i < map->size.x - 1)
		{
			if ((head->str[i] == '0' || head->str[i] == map->start)
				&& (head->str[i + 1] == ' ' || head->str[i - 1] == ' '
					|| head->prev->str[i] == ' ' || head->next->str[i] == ' '))
			{
				map_crd_error_message(scene, "Invalid map: not surrounded by walls due to:",
					head->str[i], (t_nbr){.str = ft_strdup(head->line_nbr),
					.value = i});
				exit_error(scene->tmp, scene);
			}
		}
		head = head->next;
	}
}
