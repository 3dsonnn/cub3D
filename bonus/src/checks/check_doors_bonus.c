/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_doors_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:41:26 by efinda            #+#    #+#             */
/*   Updated: 2025/05/06 16:44:18 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static void	check_points(t_scene *scene, t_door door, t_nbr aux)
{
	if (door.points[NO] == 'D' || door.points[SO] == 'D'
		|| door.points[WE] == 'D' || door.points[EA] == 'D')
	{
		map_crd_error_message(scene,
			"Invalid map: a door cannot have another door near it:", 'D', aux);
		exit_cub(scene->cub, scene->tmp);
	}
	if (door.points[NO] == ' ' || door.points[SO] == ' '
		|| door.points[WE] == ' ' || door.points[EA] == ' ')
	{
		map_crd_error_message(scene,
			"Invalid map: a door cannot have a space near it:", 'D', aux);
		exit_cub(scene->cub, scene->tmp);
	}
	ft_strfree(&aux.str);
}

static void	check_dir(t_scene *scene, t_door door, t_nbr aux)
{
	char	*tmp;

	if (door.dir.x && door.dir.y)
	{
		map_crd_error_message(scene,
			"Invalid map: a door cannot be surrounded by walls:", 'D', aux);
		exit_cub(scene->cub, scene->tmp);
	}
	if (!door.dir.x && !door.dir.y)
	{
		tmp = ft_strjoin("Invalid map: doors must be vertically or",
				"horizontally surrounded by walls:", 0);
		map_crd_error_message(scene, tmp, 'D', aux);
		ft_strfree(&tmp);
		exit_cub(scene->cub, scene->tmp);
	}
	if ((door.dir.x && (door.points[WE] == '1' || door.points[EA] == '1'))
		|| (door.dir.y && (door.points[NO] == '1' || door.points[SO] == '1')))
	{
		map_crd_error_message(scene, "Invalid map: Dead end door:", 'D', aux);
		exit_cub(scene->cub, scene->tmp);
	}
	ft_strfree(&aux.str);
}

void	check_doors(t_scene *scene, t_door door, t_row *head, t_row *tail)
{
	while (head != tail)
	{
		door.i = 0;
		while (++door.i < ft_strlen(head->str) - 1)
		{
			if (head->str[door.i] == 'D')
			{
				door.points[NO] = head->prev->str[door.i];
				door.points[SO] = head->next->str[door.i];
				door.points[WE] = head->str[door.i - 1];
				door.points[EA] = head->str[door.i + 1];
				check_points(scene, door,
					(t_nbr){.str = ft_strdup(head->line_nbr), .value = door.i});
				door.dir.x = (door.points[NO] == '1' && door.points[SO] == '1');
				door.dir.y = (door.points[WE] == '1' && door.points[EA] == '1');
				check_dir(scene, door, (t_nbr){.str = ft_strdup(head->line_nbr),
					.value = door.i});
			}
		}
		head = head->next;
	}
}
