/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:00:49 by efinda            #+#    #+#             */
/*   Updated: 2025/01/12 11:00:41 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	check_args(t_scene *scene, int ac, char **av)
{
	if (ac != 2)
		exit_error("Invalid number of arguments", scene);
	if (ft_strlen(av[1]) <= 4 || ft_strncmp(av[1] + ft_strlen(av[1]) - 4,
			".cub", 4))
		exit_error("Invalid scene file extension", scene);
	scene->fd = open(av[1], O_RDONLY);
	if (scene->fd < 0)
		exit_error(strerror(errno), scene);
	scene->line = get_next_line(scene->fd);
	if (!scene->line)
		exit_error("Empty scene file", scene);
	scene->line[ft_strlen(scene->line) - 1] = '\0';
	if (!*scene->line || ft_strspace(scene->line))
		exit_error("Invalid scene file: it cannot start with an empty line",
			scene);
}

static void	check_elements(t_scene *scene, int i)
{
	check_element(scene);
	i++;
	while (-42 && i != 6)
	{
		scene->line = get_next_line(scene->fd);
		if (!scene->line)
			exit_error("Missing elements in the scene file", scene);
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
	int	p[3];

	ft_memset(p, -1, 4 * sizeof(int));
	scene->line = get_next_line(scene->fd);
	if (!scene->line)
		exit_error("The map is missing in the scene file", scene);
	scene->line[ft_strlen(scene->line) - 1] = '\0';
	if (!*scene->line || ft_strspace(scene->line))
		escape_empty_lines(scene);
	if (ft_strspn(scene->line, "01 NSEW") != ft_strlen(scene->line))
		exit_error("aInvalid character inside the map", scene);
	map->content = ft_mtxdup(&scene->line);
	ft_strfree(&scene->line);
	fill_map(scene, map);
	if (map->size.x < 3 || map->size.y < 3)
		exit_error("Invalid map: it's too small", scene);
	check_starting_position(scene, map);
	is_surrounded(scene, map, p);
}

void	checks(t_scene *scene, int ac, char **av)
{
	scene->tmp = NULL;
	scene->line = NULL;
	scene->mtx = NULL;
	scene->map.content = NULL;
	scene->map.dx[0] = -1;
	scene->map.dx[1] = 1;
	scene->map.dx[2] = 0;
	scene->map.dx[3] = 0;
	scene->map.dy[0] = 0;
	scene->map.dy[1] = 0;
	scene->map.dy[2] = -1;
	scene->map.dy[3] = 1;
	scene->elements = NULL;
	check_args(scene, ac, av);
	check_elements(scene, 0);
	ft_strfree(&scene->elements);
	check_map(scene, &scene->map);
}
