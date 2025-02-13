/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 09:21:49 by efinda            #+#    #+#             */
/*   Updated: 2025/02/13 00:46:54 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static  void    check_duplicate_id(t_scene *scene, char ID)
{
    if (ft_strchr(scene->elements, ID))
        exit_error("Duplicate element in the scene file", scene);
    scene->tmp = ft_strjoin(scene->elements, &ID);
    ft_strfree(&scene->elements);
    ft_swaptr((void **)&scene->elements, (void **)&scene->tmp);
}

static  void	fill_texture_aux(t_scene *scene, char ID, char *path)
{
	if (ID == 'N')
	{
		scene->textures[NO].path = ft_strdup(path);
		scene->textures[NO].id = NO;
	}
	else if (ID == 'S')
	{
		scene->textures[SO].path = ft_strdup(path);
		scene->textures[SO].id = SO;
	}
	else if (ID == 'W')
	{
		scene->textures[WE].path = ft_strdup(path);
		scene->textures[WE].id = WE;
	}
	else if (ID == 'E')
	{
		scene->textures[EA].path = ft_strdup(path);
		scene->textures[EA].id = EA;
	}
	else
		exit_error("Invalid element in the scene file", scene);
}

void	fill_texture(t_scene *scene, char ID, char *path)
{
    if (!scene->elements)
		scene->elements = ft_ctoa(ID);
	else
		check_duplicate_id(scene, ID);
    fill_texture_aux(scene, ID, path);
}

void	fill_fc(t_scene *scene, char ID, int *rgb, int i)
{
	if (!scene->elements)
		scene->elements = ft_strdup(&ID);
	else
        check_duplicate_id(scene, ID);
	if (ID == 'C')
		while (++i < 3)
			scene->fc[CEILING].rgb[i] = rgb[i];
	else if (ID == 'F')
		while (++i < 3)
			scene->fc[FLOOR].rgb[i] = rgb[i];
	else
		exit_error("Invalid element in the scene file", scene);
}