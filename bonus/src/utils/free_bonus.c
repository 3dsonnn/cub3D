/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:47:58 by efinda            #+#    #+#             */
/*   Updated: 2025/03/12 15:55:34 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

void    free_tiles(t_tile ***tiles, int i, int size)
{
    if (!tiles || !*tiles || !(*tiles)[0])
        return ;
	while (++i < size)
        if ((*tiles)[i])
            free((*tiles)[i]);
    free(*tiles);
    *tiles = NULL;
}
