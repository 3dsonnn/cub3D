/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceiling_and_floor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 22:23:22 by efinda            #+#    #+#             */
/*   Updated: 2025/04/17 01:51:58 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	fill_fc(t_scene *scene, char id, int rgb[3], int i)
{
	if (!scene->elements)
		scene->elements = ft_strdup((char []){id, '\0'});
	else
		check_duplicate_id(scene, id);
	if (id == 'C')
		scene->ceiling = my_mlx_get_rgb_color(rgb[0], rgb[1], rgb[2]);
	else if (id == 'F')
		scene->floor = my_mlx_get_rgb_color(rgb[0], rgb[1], rgb[2]);
}

static void	check_color_range(t_scene *scene, int rgb[3], char *id, char *aux)
{
	if (!(rgb[0] >= 0 && rgb[0] <= 255))
	{
		scene->tmp = aux;
		exit_error(get_explicit_error_message(scene, (t_strs){"Invalid ", id,
				" element on line ", scene->line_nbr.str, ": ",
				"Red color is out of the range [0, 255]"}), scene);
	}
	if (!(rgb[1] >= 0 && rgb[1] <= 255))
	{
		scene->tmp = aux;
		exit_error(get_explicit_error_message(scene, (t_strs){"Invalid ", id,
				" element on line ", scene->line_nbr.str, ": ",
				"Green color is out of the range [0, 255]"}), scene);
	}
	if (!(rgb[2] >= 0 && rgb[2] <= 255))
	{
		scene->tmp = aux;
		exit_error(get_explicit_error_message(scene, (t_strs){"Invalid ", id,
				" element on line ", scene->line_nbr.str, ": ",
				"Blue color is out of the range [0, 255]"}), scene);
	}
	scene->tmp = aux;
	ft_strfree(&scene->tmp);
	fill_fc(scene, *id, rgb, -1);
}

static void	first_checks(t_scene *scene, char *id, int i)
{
	if (ft_strlen(scene->line) < 7)
		exit_error(get_explicit_error_message(scene, (t_strs){"Invalid ", id,
				" element on line ", scene->line_nbr.str, ": ", "too short"}),
			scene);
	while (scene->line[++i])
		if (!ft_strchr("0123456789 ,", scene->line[i]))
			exit_error(get_explicit_error_message(scene,
					(t_strs){"Invalid character on the ", id,
					" element on line ", scene->line_nbr.str, NULL, NULL}),
				scene);
	scene->mtx = ft_split(scene->line + 2, ' ');
	if (ft_mtxlen(scene->mtx) < 1)
		exit_error(get_explicit_error_message(scene, (t_strs){"Invalid ", id,
				" element on line ", scene->line_nbr.str, ": ", "too short"}),
			scene);
	if (ft_mtxlen(scene->mtx) > 5)
		exit_error(get_explicit_error_message(scene, (t_strs){"Invalid ", id,
				" element on line ", scene->line_nbr.str, ": ", "too long"}),
			scene);
	if (!ft_strcmp(*scene->mtx, ","))
		exit_error(get_explicit_error_message(scene, (t_strs){"Invalid ", id,
				" element on line ", scene->line_nbr.str, ": ",
				"the color range cannot start with a ','"}), scene);
}

static void	keep_checking(t_scene *scene, char *id, int rgb[3], int i)
{
	char	*aux;

	if (!ft_strcmp(scene->mtx[ft_mtxlen(scene->mtx) - 1], ","))
		exit_error(get_explicit_error_message(scene, (t_strs){"Invalid ", id,
				" element on line ", scene->line_nbr.str, ": ",
				"the color range cannot end with a ','"}), scene);
	while (scene->mtx[++i])
		scene->tmp = ft_strjoin_free(scene->tmp, scene->mtx[i]);
	aux = scene->tmp;
	rgb[0] = ft_atoi(scene->tmp);
	scene->tmp = ft_strchr(scene->tmp, ',');
	if (*(scene->tmp + 1) == ',')
	{
		scene->tmp = aux;
		exit_error(get_explicit_error_message(scene, (t_strs){"Invalid ", id,
				" element on line ", scene->line_nbr.str, ": ",
				"the color range cannot contain consecutive commas"}), scene);
	}
	rgb[1] = ft_atoi(scene->tmp + 1);
	scene->tmp = ft_strchr(scene->tmp + 1, ',');
	rgb[2] = ft_atoi(scene->tmp + 1);
	check_color_range(scene, rgb, id, aux);
}

void	check_fc(t_scene *scene)
{
	int		rgb[3];
	char	*id;

	id = get_element_str(*scene->line);
	if (ft_strchr_count(scene->line, ',') != 2)
		exit_error(get_explicit_error_message(scene,
				(t_strs){"Incorrect number of commas on the ", id,
				" element on line ", scene->line_nbr.str, NULL, NULL}), scene);
	first_checks(scene, id, 1);
	keep_checking(scene, id, rgb, -1);
	ft_strfree(&scene->line_nbr.str);
	ft_strfree(&scene->line);
	ft_mtxfree(&scene->mtx);
}
