/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceiling_and_floor_aux.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:36:25 by efinda            #+#    #+#             */
/*   Updated: 2025/05/06 14:15:48 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static inline char	*get_color_name(int i)
{
	if (!i)
		return ("RED");
	if (i == 1)
		return ("GREEN");
	if (i == 2)
		return ("BLUE");
	return (NULL);
}

static void	conquer(t_scene *scene, char *id, int rgb[3], int i)
{
	if (ft_strint(scene->mtx[i]))
		rgb[i] = ft_atoi(scene->mtx[i]);
	else
	{
		get_explicit_error_message(scene, (t_strs){"Invalid ", id,
			" element on line ", scene->line_nbr.str, ": ", get_color_name(i)});
		scene->tmp = ft_strjoin(scene->tmp, " not an integer", 1);
		exit_cub(scene->cub, scene->tmp);
	}
}

void	divide_to_conquer(t_scene *scene, char *id, int rgb[3], int i)
{
	scene->mtx = ft_split(scene->line, ',');
	while (scene->mtx[++i])
	{
		scene->tmp = ft_strtrim(scene->mtx[i], " ");
		if (!*scene->tmp || (ft_strspn(scene->tmp,
					DIGITS) != ft_strlen(scene->tmp)))
		{
			get_explicit_error_message(scene, (t_strs){"Invalid ", id,
				" element on line ", scene->line_nbr.str, ": ",
				get_color_name(i)});
			scene->tmp = ft_strjoin(scene->tmp,
					" color information is misconfigured", 1);
			exit_cub(scene->cub, scene->tmp);
		}
		ft_swaptr((void **)&scene->mtx[i], (void **)&scene->tmp);
		ft_strfree(&scene->tmp);
		conquer(scene, id, rgb, i);
	}
}

static void	check_fc_syntax_aux(t_scene *scene, char *info, char *id)
{
	scene->tmp = ft_strtrim(info, " ");
	if (*scene->tmp == ',')
	{
		exit_cub(scene->cub, get_explicit_error_message(scene,
				(t_strs){"Invalid ", id, " element on line ",
				scene->line_nbr.str, ": ",
				"the color range cannot start with a ','"}));
	}
	if (scene->tmp[ft_strlen(scene->tmp) - 1] == ',')
	{
		exit_cub(scene->cub, get_explicit_error_message(scene,
				(t_strs){"Invalid ", id, " element on line ",
				scene->line_nbr.str, ": ",
				"the color range cannot end with a ','"}));
	}
	info = ft_strchr(scene->tmp, ',');
	if (*(info + 1) == ',')
	{
		exit_cub(scene->cub, get_explicit_error_message(scene,
				(t_strs){"Invalid ", id, " element on line ",
				scene->line_nbr.str, ": ",
				"the color range cannot contain consecutive commas"}));
	}
	ft_swaptr((void **)&scene->line, (void **)&scene->tmp);
	ft_strfree(&scene->tmp);
}

void	check_fc_syntax(t_scene *scene, char *info, char *id)
{
	int	i;

	if (ft_strlen(info) < 5)
		exit_cub(scene->cub, get_explicit_error_message(scene,
				(t_strs){"Invalid ", id, " element on line ",
				scene->line_nbr.str, ": ", "too short"}));
	i = -1;
	while (info[++i])
		if (!ft_strchr("0123456789 ,", info[i]))
			exit_cub(scene->cub, get_explicit_error_message(scene,
					(t_strs){"Invalid character on the ", id,
					" element on line ", scene->line_nbr.str, NULL, NULL}));
	if (ft_strchr_count(info, ',') != 2)
		exit_cub(scene->cub, get_explicit_error_message(scene,
				(t_strs){"Incorrect number of commas on the ", id,
				" element on line ", scene->line_nbr.str, NULL, NULL}));
	check_fc_syntax_aux(scene, info, id);
}
