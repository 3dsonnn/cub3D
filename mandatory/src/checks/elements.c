/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:36:43 by efinda            #+#    #+#             */
/*   Updated: 2025/02/19 16:47:14 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static int	check_id(char *line, int flag)
{
	if (flag)
	{
		if (!ft_strncmp(line, "C ", 2))
			return (1);
		if (!ft_strncmp(line, "F ", 2))
			return (1);
	}
	else
	{
		if (!ft_strncmp(line, "NO ", 3))
			return (1);
		if (!ft_strncmp(line, "SO ", 3))
			return (1);
		if (!ft_strncmp(line, "WE ", 3))
			return (1);
		if (!ft_strncmp(line, "EA ", 3))
			return (1);
	}
	return (0);
}

char	*get_element_str(char c)
{
	if (c == 'N')
		return ("North");
	if (c == 'S')
		return ("South");
	if (c == 'W')
		return ("West");
	if (c == 'E')
		return ("East");
	if (c == 'F')
		return ("Floor");
	if (c == 'C')
		return ("Ceiling");
	return (NULL);
}

void	check_duplicate_id(t_scene *scene, char ID)
{
	if (ft_strchr(scene->elements, ID))
	{
		ft_strfree(&scene->aux);
		scene->aux = ft_itoa(scene->line_nbr);
		if (ID == 'C' || ID == 'F')
			exit_error(get_explicit_error_message(scene, (t_strs){"Duplicated ",
					get_element_str(ID), " element on line ", scene->aux, NULL,
					NULL}), scene);
		else
			exit_error(get_explicit_error_message(scene,
					(t_strs){"Duplicate path to the ", get_element_str(ID),
					" texture on line ", scene->aux, NULL, NULL}), scene);
	}
	scene->tmp = ft_strjoin(scene->elements, &ID);
	ft_strfree(&scene->elements);
	ft_swaptr((void **)&scene->elements, (void **)&scene->tmp);
}

void	check_element(t_scene *scene)
{
	scene->tmp = ft_strtrim(scene->line, " ");
	ft_strfree(&scene->line);
	ft_swaptr((void **)&scene->line, (void **)&scene->tmp);
	if (check_id(scene->line, 0))
		check_texture(scene);
	else if (check_id(scene->line, 1))
		check_fc(scene);
	else
	{
		ft_strfree(&scene->aux);
		scene->aux = ft_itoa(scene->line_nbr);
		exit_error(get_explicit_error_message(scene,
			(t_strs){"Invalid element on line ", scene->aux,
			" of the scene file", NULL, NULL, NULL}), scene);
	}
}
