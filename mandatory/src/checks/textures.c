/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 22:22:11 by efinda            #+#    #+#             */
/*   Updated: 2025/03/09 02:10:17 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	fill_texture(t_scene *scene, char id, char *path)
{
	if (!scene->elements)
		scene->elements = ft_ctoa(id);
	else
		check_duplicate_id(scene, id);
	if (id == 'N')
		scene->textures[NO] = (t_texture){.id = NO, .path = ft_strdup(path)};
	else if (id == 'S')
		scene->textures[SO] = (t_texture){.id = SO, .path = ft_strdup(path)};
	else if (id == 'W')
		scene->textures[WE] = (t_texture){.id = WE, .path = ft_strdup(path)};
	else if (id == 'E')
		scene->textures[EA] = (t_texture){.id = EA, .path = ft_strdup(path)};
}

static void	check_texture_aux(t_scene *scene, char *id)
{
	if (ft_mtxlen(scene->mtx) != 2)
	{
		exit_error(get_explicit_error_message(scene,
				(t_strs){"Invalid path to the ", id, " texture on line ",
				scene->line_nbr_str, NULL, NULL}), scene);
	}
	if (ft_strlen(scene->mtx[1]) < 4 || ft_strncmp(scene->mtx[1]
			+ ft_strlen(scene->mtx[1]) - 4, ".xpm", 4))
	{
		exit_error(get_explicit_error_message(scene,
				(t_strs){"Invalid extension on the path to the ", id,
				" texture on line ", scene->line_nbr_str, NULL, NULL}), scene);
	}
}

void	check_texture(t_scene *scene)
{
	char	*id;

	id = get_element_str(*scene->line);
	scene->mtx = ft_split(scene->line, ' ');
	check_texture_aux(scene, id);
	if (open(scene->mtx[1], O_RDONLY) < 0)
	{
		exit_error(get_explicit_error_message(scene,
				(t_strs){"Invalid path to the ", id, " texture on line ",
				scene->line_nbr_str, ": ", strerror(errno)}), scene);
	}
	fill_texture(scene, *id, scene->mtx[1]);
	ft_strfree(&scene->line_nbr_str);
	ft_strfree(&scene->line);
	ft_mtxfree(&scene->mtx);
}
