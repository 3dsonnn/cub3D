/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 22:22:11 by efinda            #+#    #+#             */
/*   Updated: 2025/02/19 16:14:55 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	fill_texture(t_scene *scene, char ID, char *path)
{
	if (!scene->elements)
		scene->elements = ft_ctoa(ID);
	else
		check_duplicate_id(scene, ID);
	if (ID == 'N')
		scene->textures[NO] = (t_texture){.id = NO, .path = ft_strdup(path)};
	else if (ID == 'S')
		scene->textures[SO] = (t_texture){.id = SO, .path = ft_strdup(path)};
	else if (ID == 'W')
		scene->textures[WE] = (t_texture){.id = WE, .path = ft_strdup(path)};
	else if (ID == 'E')
		scene->textures[EA] = (t_texture){.id = EA, .path = ft_strdup(path)};
}

static void	check_texture_aux(t_scene *scene, char *ID)
{
	if (ft_mtxlen(scene->mtx) != 2)
	{
		ft_mtxfree(&scene->mtx);
		scene->aux = ft_itoa(scene->line_nbr);
		exit_error(get_explicit_error_message(scene,
				(t_strs){"Invalid path to the ", ID, " texture on line ",
				scene->aux, NULL, NULL}), scene);
	}
	if (ft_strlen(scene->mtx[1]) < 4 || ft_strncmp(scene->mtx[1]
			+ ft_strlen(scene->mtx[1]) - 4, ".xpm", 4))
	{
		ft_mtxfree(&scene->mtx);
		scene->aux = ft_itoa(scene->line_nbr);
		exit_error(get_explicit_error_message(scene,
				(t_strs){"Invalid extension on the path to the ", ID,
				" texture on line ", scene->aux, NULL, NULL}), scene);
	}
}

void	check_texture(t_scene *scene)
{
	char	*ID;

	ID = get_element_str(*scene->line);
	scene->mtx = ft_split(scene->line, ' ');
	check_texture_aux(scene, ID);
	if (open(scene->mtx[1], O_RDONLY) < 0)
	{
		ft_mtxfree(&scene->mtx);
		scene->aux = ft_itoa(scene->line_nbr);
		exit_error(get_explicit_error_message(scene,
				(t_strs){"Invalid path to the ", ID, " texture on line ",
				scene->aux, ": ", strerror(errno)}), scene);
	}
	fill_texture(scene, *scene->line, scene->mtx[1]);
	ft_strfree(&scene->line);
	ft_mtxfree(&scene->mtx);
}
