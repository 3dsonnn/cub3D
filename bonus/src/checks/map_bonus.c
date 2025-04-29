/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 02:23:44 by efinda            #+#    #+#             */
/*   Updated: 2025/04/28 20:02:48 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static void	check_map_end(t_scene *scene, t_map *map)
{
	ft_strfree(&scene->line_nbr.str);
	if (!scene->line)
		return ;
	while (-42)
	{
		skip_empty_lines(scene);
		if (!scene->line)
			return ;
		scene->line_nbr.str = ft_itoa(scene->line_nbr.value);
		exit_error(get_explicit_error_message(scene,
				(t_strs){"The map content always has to be the last ",
				"information on the file. So the element on line ",
				scene->line_nbr.str, " is invalid", NULL, NULL}), scene);
	}
}

void	fulfill_map(t_scene *scene, t_map *map, t_row *head)
{
	int	len;

	while (head)
	{
		len = ft_strlen(head->str);
		if (len < map->size.x)
		{
			scene->tmp = ft_calloc(map->size.x + 1, sizeof(char));
			ft_strnfill(scene->tmp, head->str, len);
			ft_memset(scene->tmp + len, ' ', map->size.x - len);
			ft_strfree(&head->str);
			ft_swaptr((void **)&head->str, (void **)&scene->tmp);
		}
		head = head->next;
	}
}

void	fill_map(t_scene *scene, t_map *map)
{
	int	diff;

	while (-42)
	{
		scene->line = get_next_line(scene->fd);
		scene->line_nbr = (t_nbr){.value = ++scene->line_nbr.value,
			.str = ft_itoa(scene->line_nbr.value)};
		if (!scene->line || !*scene->line)
			break ;
		diff = ft_strspn(scene->line, "01 NSEWD");
		if (diff != ft_strlen(scene->line))
		{
			map_crd_error_message(scene,
				"Invalid map: strange character inside it:", *(scene->line
					+ diff), (t_nbr){.str = ft_strdup(scene->line_nbr.str),
				.value = diff});
			exit_error(scene->tmp, scene);
		}
		add_row_back(&map->head, new_row(scene->line, scene->line_nbr.value));
		ft_strfree(&scene->line_nbr.str);
		ft_strfree(&scene->line);
	}
	check_map_end(scene, map);
}

void	check_starting_position(t_scene *scene, t_map *map, t_row *head,
		t_iter iter)
{
	while (++iter.i < map->size.y)
	{
		iter.j = -1;
		while (++iter.j < map->size.x)
		{
			if (ft_strchr("NSEW", head->str[iter.j]))
			{
				map->start = head->str[iter.j];
				map->spos = (t_point){.x = iter.j, .y = iter.i};
				add_map_crd(&map->crds, new_map_crd(map->start, ft_itoa(iter.j),
						head->line_nbr));
				iter.k++;
			}
		}
		head = head->next;
	}
	if (!iter.k)
		exit_error("Invalid map: there isn't a start position", scene);
	if (iter.k > 1)
	{
		scene->tmp = map_crds_to_str(map->crds,
				"Invalid map: there're more than one start position:");
		exit_error(scene->tmp, scene);
	}
	free_map_crds(&scene->map.crds);
}
