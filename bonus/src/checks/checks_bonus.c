/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:00:49 by efinda            #+#    #+#             */
/*   Updated: 2025/04/28 19:56:57 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static void	check_args(t_scene *scene, int ac, char **av)
{
	if (ac != 2)
		exit_error("Invalid number of arguments", scene);
	if (ft_strlen(av[1]) < 4 || ft_strcmp(av[1] + ft_strlen(av[1]) - 4, ".cub"))
		exit_error("Invalid scene file extension", scene);
	scene->fd = open(av[1], O_RDONLY);
	if (scene->fd < 0)
		exit_error(strerror(errno), scene);
	scene->line = get_next_line(scene->fd);
	if (!scene->line)
		exit_error("Empty scene file", scene);
	scene->line_nbr.value++;
	if (!*scene->line)
	{
		skip_empty_lines(scene);
		if (!scene->line)
			exit_error("There aren't elements in the scene file", scene);
	}
	check_element(scene);
}

static void	check_elements(t_scene *scene)
{
	while (-42)
	{
		scene->line = get_next_line(scene->fd);
		if (!scene->line)
		{
			if (ft_strlen(scene->elements) == 6)
				exit_error("The map is missing in the scene file", scene);
			exit_error("Missing elements in the scene file", scene);
		}
		scene->line_nbr.value++;
		if (!*scene->line)
		{
			ft_strfree(&scene->line);
			continue ;
		}
		scene->line_cpy = ft_strdup(scene->line);
		check_element(scene);
		ft_strfree(&scene->line_cpy);
		if (scene->line)
			break ;
	}
	ft_strfree(&scene->elements);
}

static void	check_map(t_scene *scene, t_map *map)
{
	add_row_back(&map->head, new_row(scene->line, scene->line_nbr.value));
	ft_strfree(&scene->line);
	fill_map(scene, map);
	trim_rows(&map->head);
	if (!map->head)
		exit_error(get_explicit_error_message(scene,
				(t_strs){"Invalid map: it cannot be full of spaces", NULL, NULL,
				NULL, NULL, NULL}), scene);
	map->size = rows_size(map->head);
	if (map->size.x < 3 || map->size.y < 3)
		exit_error(get_explicit_error_message(scene,
				(t_strs){"Invalid map: too small", NULL, NULL, NULL, NULL,
				NULL}), scene);
	fulfill_map(scene, map, map->head);
	map->size.x = ft_strlen(map->head->str);
	check_starting_position(scene, map, map->head, (t_iter){-1, -1, 0, -1, -1,
		-1});
	check_doors(scene, map->door, map->head->next, get_last_row(map->head));
	is_surrounded(scene, map, map->head->next, get_last_row(map->head));
	trim_rows_horizontally(&map->head, get_horizontal_limits(map->head,
			(t_point){.x = map->size.x, .y = map->size.x}, (t_point){.x = 0,
			.y = 0}));
	update_player(map, map->head);
	extend_map(map, &map->head, map->head);
	map->content = row_to_mtx(map->head);
	map->content[map->spos.y][map->spos.x] = '0';
	free_rows(&map->head);
}

void	checks(t_cub *cub, int ac, char **av)
{
	check_args(&cub->scene, ac, av);
	check_elements(&cub->scene);
	check_map(&cub->scene, &cub->scene.map);
}
