/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 02:23:44 by efinda            #+#    #+#             */
/*   Updated: 2025/03/03 22:24:10 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	check_map_start(t_scene *scene, t_map *map)
{
	scene->line = get_next_line(scene->fd);
	scene->line_nbr++;
	if (!scene->line)
		exit_error("The map is missing in the scene file", scene);
	if (scene->line[ft_strlen(scene->line) - 1] == '\n')
		scene->line[ft_strlen(scene->line) - 1] = '\0';
	if (!*scene->line)
	{
		ft_strfree(&scene->line);
		scene->tmp = skip_empty_lines(scene);
		if (!scene->tmp)
			exit_error("The map is missing in the scene file", scene);
		scene->tmp = NULL;
	}
	if (ft_strspn(scene->line, "01 NSEW") != ft_strlen(scene->line))
	{
		scene->line_nbr_str = ft_itoa(scene->line_nbr);
		exit_error(get_explicit_error_message(scene,
				(t_strs){"Invalid element on line ", scene->line_nbr_str,
				" of the scene file", NULL, NULL, NULL}), scene);
	}
	add_row(&map->head, new_row(scene->line));
	ft_strfree(&scene->line);
}

static void	check_map_end(t_scene *scene)
{
	ft_strfree(&scene->line_nbr_str);
	if (!scene->line)
		return ;
	ft_strfree(&scene->line);
	while (-42)
	{
		scene->line = skip_empty_lines(scene);
		if (!scene->line)
			return ;
		scene->line_nbr_str = ft_itoa(scene->line_nbr);
		exit_error(get_explicit_error_message(scene,
				(t_strs){"The map content always has to be the last information on the file. So the element on line ",
				scene->line_nbr_str, " is invalid", NULL, NULL, NULL}), scene);
	}
}

void	fulfill_map(t_scene *scene, t_map *map)
{
	int	i;
	int	len;

	i = -1;
	while (++i < map->size.y)
	{
		len = ft_strlen(map->content[i]);
		if (len < map->size.x)
		{
			scene->tmp = ft_calloc(map->size.x + 1, sizeof(char));
			ft_strnfill(scene->tmp, map->content[i], len);
			ft_memset(scene->tmp + len, ' ', map->size.x - len);
			ft_strfree(&map->content[i]);
			ft_swaptr((void **)&map->content[i], (void **)&scene->tmp);
		}
	}
}

void	fill_map(t_scene *scene, t_map *map)
{
	while (-42)
	{
		scene->line = get_next_line(scene->fd);
		scene->line_nbr++;
		scene->line_nbr_str = ft_itoa(scene->line_nbr);
		if (!scene->line)
			break ;
		if (scene->line[ft_strlen(scene->line) - 1] == '\n')
			scene->line[ft_strlen(scene->line) - 1] = '\0';
		if (!*scene->line)
			break ;
		if (ft_strspn(scene->line, "01 NSEW") != ft_strlen(scene->line))
		{
			exit_error(get_explicit_error_message(scene,
					(t_strs){"Invalid character inside the map content on line ",
					scene->line_nbr_str, " of the scene file", NULL, NULL,
					NULL}), scene);
		}
		add_row(&map->head, new_row(scene->line));
		ft_strfree(&scene->line);
		ft_strfree(&scene->line_nbr_str);
	}
	check_map_end(scene);
	map->content = row_to_mtx(map->head);
	free_rows(&map->head);
}

void	check_starting_position(t_scene *scene, t_map *map, int i, int j)
{
	int	flag;

	flag = 0;
	while (++i < map->size.y)
	{
		j = -1;
		while (++j < map->size.x)
		{
			if (ft_strchr("NSEW", map->content[i][j]))
			{
				map->start = map->content[i][j];
				map->content[i][j] = '0';
				map->spos.x = j;
				map->spos.y = i;
				flag++;
			}
		}
	}
	if (!flag)
		exit_error("Invalid map: there isn't a start position", scene);
	if (flag > 1)
		exit_error("Invalid map: there's more than one start position", scene);
}
