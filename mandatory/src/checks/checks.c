/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:00:49 by efinda            #+#    #+#             */
/*   Updated: 2025/02/17 06:38:06 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	check_args(t_scene *scene, int ac, char **av)
{
	if (ac != 2)
		exit_error("Invalid number of arguments", scene);
	if (ft_strlen(av[1]) < 4 || ft_strncmp(av[1] + ft_strlen(av[1]) - 4,
			".cub", 4))
		exit_error("Invalid scene file extension", scene);
	scene->fd = open(av[1], O_RDONLY);
	if (scene->fd < 0)
		exit_error(strerror(errno), scene);
	scene->line = get_next_line(scene->fd);
	if (!scene->line)
		exit_error("Empty scene file", scene);
	// if (ft_strchr(scene->line, '\t') || )
	scene->line[ft_strlen(scene->line) - 1] = '\0';
}

static void	check_elements(t_scene *scene, int i)
{
	check_element(scene);
	i++;
	while (i != 6)
	{
		scene->line = get_next_line(scene->fd);
		if (!scene->line)
			exit_error("Missing elements in the scene file", scene);
		if (scene->line[ft_strlen(scene->line) - 1] == '\n')
			scene->line[ft_strlen(scene->line) - 1] = '\0';
		if (!*scene->line || ft_strspace(scene->line))
		{
			ft_strfree(&scene->line);
			continue ;
		}
		check_element(scene);
		i++;
	}
	if (i != 6)
		exit_error("Missing elements in the scene file", scene);
}

static void	check_map(t_scene *scene, t_map *map)
{
	scene->line = get_next_line(scene->fd);
	if (!scene->line)
		exit_error("The map is missing in the scene file", scene);
	if (scene->line[ft_strlen(scene->line) - 1] == '\n')
		scene->line[ft_strlen(scene->line) - 1] = '\0';
	if (!*scene->line || ft_strspace(scene->line))
		escape_empty_lines(scene);
	if (ft_strspn(scene->line, "01 NSEW") != ft_strlen(scene->line))
		exit_error("Invalid character inside the map", scene);
	add_row(&map->head, new_row(scene->line));
	ft_strfree(&scene->line);
	fill_map(scene, map);
	if (map->size.x < 3 || map->size.y < 3)
		exit_error("Invalid map: it's too small", scene);
	check_starting_position(scene, map, -1, -1);
	is_surrounded(scene, map);
}

static	void    init_scene(t_scene *scene)
{
    scene->tmp = NULL;
	scene->line = NULL;
	scene->elements = NULL;
	scene->map.head = NULL;
	scene->map.content = NULL;
	scene->textures[NO].path = NULL;
	scene->textures[SO].path = NULL;
	scene->textures[WE].path = NULL;
	scene->textures[EA].path = NULL;
}

void	checks(t_cub *cub, int ac, char **av)
{
	init_scene(&cub->scene);
	check_args(&cub->scene, ac, av);
	check_elements(&cub->scene, 0);
	ft_strfree(&cub->scene.elements);
	check_map(&cub->scene, &cub->scene.map);
}
