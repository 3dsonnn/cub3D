/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:22:09 by efinda            #+#    #+#             */
/*   Updated: 2025/04/30 16:32:42 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	exit_error(char *message, t_scene *scene)
{
	int	i;

	i = write(2, "Error\n", 6);
	i = write(2, message, ft_strlen(message));
	i = write(2, "\n", 1);
	ft_mtxfree(&scene->mtx);
	ft_strfree(&scene->tmp);
	ft_strfree(&scene->line);
	ft_strfree(&scene->line_cpy);
	free_rows(&scene->map.head);
	free_map_crds(&scene->map.crds);
	ft_strfree(&scene->elements);
	ft_mtxfree(&scene->map.content);
	ft_strfree(&scene->line_nbr.str);
	i = -1;
	while (++i < 4)
		ft_strfree(&scene->textures[i].path);
	exit(1);
}

void	map_crd_error_message(t_scene *scene, char *message, char c, t_nbr aux)
{
	add_map_crd(&scene->map.crds, new_map_crd(c, ft_itoa(aux.value), aux.str));
	scene->tmp = map_crds_to_str(scene->map.crds, message);
	ft_strfree(&aux.str);
}
