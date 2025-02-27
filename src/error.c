/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welepy <welepy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:22:09 by efinda            #+#    #+#             */
/*   Updated: 2025/01/12 10:16:31 by welepy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void    exit_error(char *message, t_scene *scene)
{
    int return_value;

    return_value = write(2, "Error\n", 6);
    return_value = write(2, message, ft_strlen(message));
    return_value = write(2, "\n", 1);
    ft_strfree(&scene->tmp);
    ft_strfree(&scene->line);
    ft_strfree(&scene->elements);
    ft_mtxfree(&scene->mtx);
    ft_mtxfree(&scene->map.content);
    (void)return_value;
    exit(1);
}