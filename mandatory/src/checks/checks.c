/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:00:49 by efinda            #+#    #+#             */
/*   Updated: 2025/04/22 18:03:55 by efinda           ###   ########.fr       */
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

void	print_rows(t_row *head)
{
	if (!head)
	{
		ft_printf("EMPTY\n");
        return ;
	}
	while (head)
	{
		ft_printf("id=%d-->%s\n", head->line_nbr.value, head->str);
		head = head->next;
	}
}

void trim_rows(t_row **head)
{
    t_row *aux;
    t_row *tmp;

    if (!head || !*head)
        return ;
    tmp = *head;
    while (tmp && ft_strspace(tmp->str))
    {
        aux = tmp;
        tmp = tmp->next;
        free_row(&aux, aux);
    }
    *head = tmp;
    if (!*head)
        return ;
    aux = tmp;
    while (aux->next && !ft_strspace(aux->next->str))
        aux = aux->next;
    while (aux->next && ft_strspace(aux->next->str))
    {
        tmp = aux->next;
        aux->next = tmp->next;
        if (tmp->next)
            tmp->next->prev = aux;
        free_row(&tmp, tmp);
    }
}

static void	check_map(t_scene *scene, t_map *map)
{
	add_row(&map->head, new_row(scene->line, scene->line_nbr.value));
	ft_strfree(&scene->line);
	fill_map(scene, map);
	map->content = row_to_mtx(map->head);
	print_rows(map->head);
	trim_rows(&map->head);
	ft_printf("-----------------------------------------\n");
	print_rows(map->head);
	// free_rows(&map->head);
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
	check_args(&cub->scene, ac, av);
	check_elements(&cub->scene);
	check_map(&cub->scene, &cub->scene.map);
}
