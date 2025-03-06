/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceiling_and_floor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 22:23:22 by efinda            #+#    #+#             */
/*   Updated: 2025/03/06 05:01:42 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	fill_fc(t_scene *scene, char ID, int rgb[3], int i)
{
	if (!scene->elements)
		scene->elements = ft_strdup((char []){ID, '\0'});
	else
		check_duplicate_id(scene, ID);
	if (ID == 'C')
		scene->ceiling = my_mlx_get_rgb_color(rgb[0], rgb[1], rgb[2]);
	else if (ID == 'F')
		scene->floor = my_mlx_get_rgb_color(rgb[0], rgb[1], rgb[2]);
}

static void	check_color_range(t_scene *scene, int rgb[3], char *ID, char *aux)
{
	if (!(rgb[0] >= 0 && rgb[0] <= 255))
	{
		scene->tmp = aux;
		exit_error(get_explicit_error_message(scene, (t_strs){"Invalid ", ID,
				" element on line ", scene->line_nbr_str, ": ",
				"Red color is out of the range [0, 255]"}), scene);
	}
	if (!(rgb[1] >= 0 && rgb[1] <= 255))
	{
		scene->tmp = aux;
		exit_error(get_explicit_error_message(scene, (t_strs){"Invalid ", ID,
				" element on line ", scene->line_nbr_str, ": ",
				"Green color is out of the range [0, 255]"}), scene);
	}
	if (!(rgb[2] >= 0 && rgb[2] <= 255))
	{
		scene->tmp = aux;
		exit_error(get_explicit_error_message(scene, (t_strs){"Invalid ", ID,
				" element on line ", scene->line_nbr_str, ": ",
				"Blue color is out of the range [0, 255]"}), scene);
	}
	scene->tmp = aux;
	ft_strfree(&scene->tmp);
	fill_fc(scene, *ID, rgb, -1);
}

static void	first_checks(t_scene *scene, char *ID, int i)
{
	if (ft_strchr_count(scene->line, ',') != 2)
		exit_error(get_explicit_error_message(scene,
				(t_strs){"Incorrect number of commas on the ", ID,
				" element on line ", scene->line_nbr_str, NULL, NULL}), scene);
	if (ft_strlen(scene->line) < 7)
		exit_error(get_explicit_error_message(scene, (t_strs){"Invalid ", ID,
				" element on line ", scene->line_nbr_str, ": ", "too short"}), scene);
	while (scene->line[++i])
		if (!ft_strchr("0123456789 ,", scene->line[i]))
			exit_error(get_explicit_error_message(scene,
					(t_strs){"Invalid character on the ", ID,
					" element on line ", scene->line_nbr_str, NULL, NULL}), scene);
	scene->mtx = ft_split(scene->line + 2, ' ');
	if (ft_mtxlen(scene->mtx) < 1)
		exit_error(get_explicit_error_message(scene, (t_strs){"Invalid ", ID,
				" element on line ", scene->line_nbr_str, ": ", "too short"}), scene);
	if (ft_mtxlen(scene->mtx) > 5)
		exit_error(get_explicit_error_message(scene, (t_strs){"Invalid ", ID,
				" element on line ", scene->line_nbr_str, ": ", "too long"}), scene);
	if (!ft_strcmp(*scene->mtx, ","))
		exit_error(get_explicit_error_message(scene, (t_strs){"Invalid ", ID,
				" element on line ", scene->line_nbr_str, ": ",
				"the color range cannot start with a ','"}), scene);
}

static void	keep_checking(t_scene *scene, char *ID, int rgb[3], int i)
{
	char	*aux;

	if (!ft_strcmp(scene->mtx[ft_mtxlen(scene->mtx) - 1], ","))
		exit_error(get_explicit_error_message(scene, (t_strs){"Invalid ", ID,
				" element on line ", scene->line_nbr_str, ": ",
				"the color range cannot end with a ','"}), scene);
	while (scene->mtx[++i])
		scene->tmp = ft_strjoin_free(scene->tmp, scene->mtx[i]);
	aux = scene->tmp;
	rgb[0] = ft_atoi(scene->tmp);
	scene->tmp = ft_strchr(scene->tmp, ',');
	if (*(scene->tmp + 1) == ',')
	{
		scene->tmp = aux;
		exit_error(get_explicit_error_message(scene, (t_strs){"Invalid ", ID,
				" element on line ", scene->line_nbr_str, ": ",
				"the color range cannot contain consecutive commas"}), scene);
	}
	rgb[1] = ft_atoi(scene->tmp + 1);
	scene->tmp = ft_strchr(scene->tmp + 1, ',');
	rgb[2] = ft_atoi(scene->tmp + 1);
	check_color_range(scene, rgb, ID, aux);
}

void	check_fc(t_scene *scene)
{
	int		rgb[3];
	char	*ID;
	
	ID = get_element_str(*scene->line);
	first_checks(scene, ID, 1);
	keep_checking(scene, ID, rgb, -1);
	ft_strfree(&scene->line_nbr_str);
	ft_strfree(&scene->line);
	ft_mtxfree(&scene->mtx);
}
