/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:22:09 by efinda            #+#    #+#             */
/*   Updated: 2025/01/11 17:38:01 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void    exit_error(char *message, t_scene *scene)
{
    write(2, "Error\n", 6);
    write(2, message, ft_strlen(message));
    write(2, "\n", 1);
    ft_strfree(&scene->tmp);
    ft_strfree(&scene->line);
    ft_strfree(&scene->elements);
    ft_mtxfree(&scene->mtx);
    ft_mtxfree(&scene->map.content);
	exit(1);
}