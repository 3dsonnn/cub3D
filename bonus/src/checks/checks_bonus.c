/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:00:49 by efinda            #+#    #+#             */
/*   Updated: 2025/05/07 18:14:17 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static void	check_args(t_scene *scene, int ac, char **av)
{
	if (ac != 2)
		exit_cub(scene->cub, "Invalid number of arguments");
	if (ft_strlen(av[1]) <= 4 || ft_strcmp(av[1] + ft_strlen(av[1]) - 4, ".cub"))
		exit_cub(scene->cub, "Invalid scene file extension");
	scene->fd = open(av[1], O_RDONLY);
	if (scene->fd < 0)
		exit_cub(scene->cub, strerror(errno));
	scene->line = get_next_line(scene->fd);
	if (!scene->line)
		exit_cub(scene->cub, "Empty scene file");
	scene->line_nbr.value++;
	if (!*scene->line)
	{
		skip_empty_lines(scene);
		if (!scene->line)
			exit_cub(scene->cub, "There aren't elements in the scene file");
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
				exit_cub(scene->cub, "The map is missing in the scene file");
			exit_cub(scene->cub, "Missing elements in the scene file");
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
	trim_rows_vertically(&map->head);
	if (!map->head)
		exit_cub(scene->cub, get_explicit_error_message(scene,
				(t_strs){"Invalid map: it cannot be full of spaces", NULL, NULL,
				NULL, NULL, NULL}));
	map->size = rows_size(map->head);
	if (map->size.x < 3 || map->size.y < 3)
		exit_cub(scene->cub, get_explicit_error_message(scene,
				(t_strs){"Invalid map: too small", NULL, NULL, NULL, NULL,
				NULL}));
	fulfill_map(scene, map, map->head);
	map->size.x = ft_strlen(map->head->str);
	check_starting_position(scene, map, map->head, (t_iter){-1, -1, 0, -1, -1,
		-1});
	check_doors(scene, map->door, map->head->next, get_last_row(map->head));
	is_surrounded(scene, map, map->head->next, get_last_row(map->head));
	trim_rows_horizontally(&map->head, get_horizontal_limits(map->head));
	update_map(map, map->head);
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
