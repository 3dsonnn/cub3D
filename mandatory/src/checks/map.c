/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 02:23:44 by efinda            #+#    #+#             */
/*   Updated: 2025/02/19 16:40:43 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static	void	fill_map_aux(t_scene *scene, t_map *map)
{
	int i;
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
static	void	check_last_lines(t_scene *scene)
{
	if (!scene->line)
		return ;
	ft_strfree(&scene->line);
	while (-42)
	{
		scene->line = get_next_line(scene->fd);
		if (!scene->line)
			break ;
		if (scene->line[ft_strlen(scene->line) - 1] == '\n')
			scene->line[ft_strlen(scene->line) - 1] = '\0';
		if (!*scene->line && ft_strspace(scene->line))
			exit_error("The map content always has to be the last information on the file", scene);
		ft_strfree(&scene->line);
	}
}

void	fill_map(t_scene *scene, t_map *map)
{
	while (-42)
	{
		scene->line = get_next_line(scene->fd);
		if (!scene->line)
			break ;
		if (scene->line[ft_strlen(scene->line) - 1] == '\n')
			scene->line[ft_strlen(scene->line) - 1] = '\0';
		if (!*scene->line || ft_strspace(scene->line))
			break ;
		if (ft_strspn(scene->line, "01 NSEW") != ft_strlen(scene->line))
			exit_error("Invalid character inside the map", scene);
		add_row(&map->head, new_row(scene->line));
        ft_strfree(&scene->line);
	}
	check_last_lines(scene);
	map->content = row_to_mtx(map->head);
	free_rows(&map->head);
	fill_map_aux(scene, map);
    map->size.x = ft_strlen(*map->content);
    map->size.y = ft_mtxlen(map->content);
}

char	*skip_empty_lines(t_scene *scene)
{
	while (-42)
	{
		scene->line = get_next_line(scene->fd);
		scene->line_nbr++;
		if (!scene->line)
			return (scene->line);
		if (scene->line[ft_strlen(scene->line) - 1] == '\n')
			scene->line[ft_strlen(scene->line) - 1] = '\0';
		if (!*scene->line)
		{
			ft_strfree(&scene->line);
			continue ;
		}
		return (scene->line);
	}
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
