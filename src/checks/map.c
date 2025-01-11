/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 02:23:44 by efinda            #+#    #+#             */
/*   Updated: 2025/01/11 19:28:44 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	escape_empty_lines(t_scene *scene)
{
	ft_strfree(&scene->line);
	while (-42)
	{
		scene->line = get_next_line(scene->fd);
		if (!scene->line)
			exit_error("The map is missing in the scene file", scene);
		scene->line[ft_strlen(scene->line) - 1] = '\0';
		if (!*scene->line || ft_strspace(scene->line))
		{
			ft_strfree(&scene->line);
			continue ;
		}
        break ;
	}
}

void	fill_map(t_scene *scene, t_map *map)
{
	while (-42)
	{
		scene->line = get_next_line(scene->fd);
		if (!scene->line)
			break ;
		scene->line[ft_strlen(scene->line) - 1] = '\0';
		if (!*scene->line || ft_strspace(scene->line))
			exit_error("There cannot be empty lines inside the map content", scene);
		if (ft_strcspn(scene->line, "01 NSEW") != ft_strlen(scene->line))
			exit_error("Invalid character inside the map", scene);
        scene->mtx = ft_mtxdup(map->content);
        ft_mtxfree(&map->content);
        ft_addstr_mtx(&map->content, scene->mtx, scene->line);
        ft_strfree(&scene->line);
	}
    map->rows = ft_mtxlen(map->content);
    map->cols = ft_longestr_mtx(map->content);
}
