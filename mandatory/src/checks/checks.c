/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:00:49 by efinda            #+#    #+#             */
/*   Updated: 2025/04/17 07:43:22 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

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
	if (scene->line[ft_strlen(scene->line) - 1] == '\n')
		scene->line[ft_strlen(scene->line) - 1] = '\0';
	if (!*scene->line)
	{
		ft_strfree(&scene->line);
		skip_empty_lines(scene);
		if (!scene->line)
			exit_error("There aren't elements in the scene file", scene);
	}
	scene->line_nbr.str = ft_itoa(scene->line_nbr.value);
	check_element(scene, &ac);
}

static void	check_elements(t_scene *scene, int *flag)
{
	while (-42)
	{
		scene->line = get_next_line(scene->fd);
		scene->line_nbr = (t_nbr){.value = scene->line_nbr.value++,
			.str = ft_itoa(scene->line_nbr.value)};
		if (!scene->line)
		{
			if (ft_strlen(scene->elements) == 6)
				exit_error("The map is missing in the scene file", scene);
			exit_error("Missing elements in the scene file", scene);
		}
		if (scene->line[ft_strlen(scene->line) - 1] == '\n')
			scene->line[ft_strlen(scene->line) - 1] = '\0';
		if (!*scene->line)
		{
			ft_strfree(&scene->line_nbr.str);
			ft_strfree(&scene->line);
			continue ;
		}
		if (ft_strlen(scene->elements) == 6
			&& ft_strspn(scene->line, " ") == ft_strlen(scene->line))
		{
			*flag = 1;
			return ;
		}
		check_element(scene, flag);
		if (*flag)
			return ;
	}
}

static void	check_map(t_scene *scene, t_map *map)
{
	check_map_start(scene, map);
	fill_map(scene, map);
	map->content = row_to_mtx(map->head);
	free_rows(&map->head);
	map->size.x = ft_longestr_mtx(map->content);
	map->size.y = ft_mtxlen(map->content);
	if (map->size.x < 3 || map->size.y < 3)
		exit_error(get_explicit_error_message(scene,
				(t_strs){"Invalid map: too small", NULL, NULL, NULL, NULL,
				NULL}), scene);
	fulfill_map(scene, map);
	check_starting_position(scene, map, -1, -1);
	is_surrounded(scene, map, (t_point){0, 0});
}

void	checks(t_cub *cub, int ac, char **av)
{
	int	flag;

	flag = 0;
	check_args(&cub->scene, ac, av);
	check_elements(&cub->scene, &flag);
	ft_strfree(&cub->scene.line_nbr.str);
	ft_strfree(&cub->scene.elements);
	if (!flag)
	{
		cub->scene.line = get_next_line(cub->scene.fd);
		cub->scene.line_nbr.value++;
	}
	check_map(&cub->scene, &cub->scene.map);
}
