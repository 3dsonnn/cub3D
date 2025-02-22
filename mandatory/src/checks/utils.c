/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 03:49:02 by efinda            #+#    #+#             */
/*   Updated: 2025/02/22 21:59:13 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

char	*skip_empty_lines(t_scene *scene)
{
	while (-42)
	{
		scene->line = get_next_line(scene->fd);
		scene->line_nbr++;
		if (!scene->line)
			return (scene->line);
		if (scene->line[ft_strlen(scene->line) - 1] == '\n')
			scene->line[ft_strlen(scene->line) - 1] = '\0';
		if (!*scene->line)
		{
			ft_strfree(&scene->line);
			continue ;
		}
		return (scene->line);
	}
}

char	*get_explicit_error_message(t_scene *scene, t_strs strs)
{
	ft_strfree(&scene->tmp);
	if (strs.s1)
		scene->tmp = ft_strdup(strs.s1);
	if (strs.s2)
		scene->tmp = ft_strjoin_free(scene->tmp, strs.s2);
	if (strs.s3)
		scene->tmp = ft_strjoin_free(scene->tmp, strs.s3);
	if (strs.s4)
		scene->tmp = ft_strjoin_free(scene->tmp, strs.s4);
	if (strs.s5)
		scene->tmp = ft_strjoin_free(scene->tmp, strs.s5);
	if (strs.s6)
		scene->tmp = ft_strjoin_free(scene->tmp, strs.s6);
	return (scene->tmp);
}
