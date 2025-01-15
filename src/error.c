/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:22:09 by efinda            #+#    #+#             */
/*   Updated: 2025/01/13 20:28:15 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void    exit_error(char *message, t_scene *scene)
{
    int i;

    i = write(2, "Error\n", 6);
    i = write(2, message, ft_strlen(message));
    i = write(2, "\n", 1);
    ft_strfree(&scene->tmp);
    ft_strfree(&scene->line);
    free_rows(&scene->map.head);
    ft_strfree(&scene->elements);
    ft_mtxfree(&scene->map.content);
    i = -1;
    while (++i < 4)
    {
        ft_strfree(&scene->walls[i].path);
    }
    exit(1);
}