/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceiling_and_floor_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 22:23:22 by efinda            #+#    #+#             */
/*   Updated: 2025/05/06 15:47:38 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static void	fill_fc(t_scene *scene, char id, int rgb[3])
{
	if (!scene->elements)
		scene->elements = ft_strdup((char[]){id, '\0'});
	else
		check_duplicate_id(scene, id);
	if (id == 'C')
		scene->ceiling = my_mlx_get_rgb_color(rgb[0], rgb[1], rgb[2]);
	else if (id == 'F')
		scene->floor = my_mlx_get_rgb_color(rgb[0], rgb[1], rgb[2]);
}

static void	check_color_range(t_scene *scene, int rgb[3], char *id)
{
	if (!(rgb[0] >= 0 && rgb[0] <= 255))
		exit_cub(scene->cub, get_explicit_error_message(scene,
				(t_strs){"Invalid ", id, " element on line ",
				scene->line_nbr.str, ": Red color ",
				"is out of the range [0, 255]"}));
	if (!(rgb[1] >= 0 && rgb[1] <= 255))
		exit_cub(scene->cub, get_explicit_error_message(scene,
				(t_strs){"Invalid ", id, " element on line ",
				scene->line_nbr.str, ": Green color ",
				"is out of the range [0, 255]"}));
	if (!(rgb[2] >= 0 && rgb[2] <= 255))
		exit_cub(scene->cub, get_explicit_error_message(scene,
				(t_strs){"Invalid ", id, " element on line ",
				scene->line_nbr.str, ": Blue color ",
				"is out of the range [0, 255]"}));
	ft_strfree(&scene->tmp);
	fill_fc(scene, *id, rgb);
}

void	check_fc(t_scene *scene)
{
	int		rgb[3];
	char	*id;

	id = get_element_name(*scene->line);
	check_fc_syntax(scene, scene->line + 2, id);
	divide_to_conquer(scene, id, rgb, -1);
	check_color_range(scene, rgb, id);
	ft_strfree(&scene->line_nbr.str);
	ft_strfree(&scene->line_cpy);
	ft_strfree(&scene->line);
	ft_mtxfree(&scene->mtx);
}
