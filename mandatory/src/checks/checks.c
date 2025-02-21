/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:00:49 by efinda            #+#    #+#             */
/*   Updated: 2025/02/21 13:18:30 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	check_args(t_scene *scene, int ac, char **av)
{
	if (ac != 2)
		exit_error("Invalid number of arguments", scene);
	if (ft_strlen(av[1]) < 4 || ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub",
			4))
		exit_error("Invalid scene file extension", scene);
	scene->fd = open(av[1], O_RDONLY);
	if (scene->fd < 0)
		exit_error(strerror(errno), scene);
	scene->line = get_next_line(scene->fd);
	if (!scene->line)
		exit_error("Empty scene file", scene);
	scene->line_nbr++;
	if (scene->line[ft_strlen(scene->line) - 1] == '\n')
		scene->line[ft_strlen(scene->line) - 1] = '\0';
	if (!*scene->line)
	{
		ft_strfree(&scene->line);
		scene->tmp = skip_empty_lines(scene);
		if (!scene->tmp)
			exit_error("There aren't elements in the scene file", scene);
		scene->tmp = NULL;
	}
}

static void	check_elements(t_scene *scene)
{
	check_element(scene);
	while (-42)
	{
		scene->line = get_next_line(scene->fd);
		scene->line_nbr++;
		scene->line_nbr_str = ft_itoa(scene->line_nbr);
		if (!scene->line)
			exit_error("Missing elements in the scene file", scene);
		if (scene->line[ft_strlen(scene->line) - 1] == '\n')
			scene->line[ft_strlen(scene->line) - 1] = '\0';
		if (!*scene->line)
		{
			ft_strfree(&scene->line_nbr_str);
			ft_strfree(&scene->line);
			continue ;
		}
		check_element(scene);
		if (ft_strlen(scene->elements) == 6)
			break ;
	}
	ft_strfree(&scene->line_nbr_str);
	ft_strfree(&scene->elements);
}

static void	check_map_aux(t_scene *scene, t_map *map)
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

static void	check_map(t_scene *scene, t_map *map)
{
	check_map_aux(scene, map);
	fill_map(scene, map);
	map->size.x = ft_strlen(*map->content);
	map->size.y = ft_mtxlen(map->content);
	fulfill_map(scene, map);
	if (map->size.x < 3 || map->size.y < 3)
		exit_error(get_explicit_error_message(scene,
				(t_strs){"Invalid map: too small", NULL, NULL, NULL, NULL,
				NULL}), scene);
	check_starting_position(scene, map, -1, -1);
	is_surrounded(scene, map);
}

void	checks(t_cub *cub, int ac, char **av)
{
	cub->scene.tmp = NULL;
	cub->scene.mtx = NULL;
	cub->scene.line = NULL;
	cub->scene.line_nbr = 0;
	cub->scene.elements = NULL;
	cub->scene.map.head = NULL;
	cub->scene.map.content = NULL;
	cub->scene.line_nbr_str = NULL;
	cub->scene.textures[NO].path = NULL;
	cub->scene.textures[SO].path = NULL;
	cub->scene.textures[WE].path = NULL;
	cub->scene.textures[EA].path = NULL;
	check_args(&cub->scene, ac, av);
	check_elements(&cub->scene);
	check_map(&cub->scene, &cub->scene.map);
}
