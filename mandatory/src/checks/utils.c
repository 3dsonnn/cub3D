/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 03:49:02 by efinda            #+#    #+#             */
/*   Updated: 2025/04/22 10:46:58 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	skip_empty_lines(t_scene *scene)
{
	ft_strfree(&scene->line);
	while (-42)
	{
		scene->line = get_next_line(scene->fd);
		if (!scene->line)
			return ;
		scene->line_nbr.value++;
		if (!*scene->line)
		{
			ft_strfree(&scene->line);
			continue ;
		}
		return ;
	}
}

char	*get_explicit_error_message(t_scene *scene, t_strs strs)
{
	ft_strfree(&scene->tmp);
	if (strs.s1)
		scene->tmp = ft_strdup(strs.s1);
	if (strs.s2)
		scene->tmp = ft_strjoin(scene->tmp, strs.s2, 1);
	if (strs.s3)
		scene->tmp = ft_strjoin(scene->tmp, strs.s3, 1);
	if (strs.s4)
		scene->tmp = ft_strjoin(scene->tmp, strs.s4, 1);
	if (strs.s5)
		scene->tmp = ft_strjoin(scene->tmp, strs.s5, 1);
	if (strs.s6)
		scene->tmp = ft_strjoin(scene->tmp, strs.s6, 1);
	return (scene->tmp);
}
