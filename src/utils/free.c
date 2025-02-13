/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:03:40 by efinda            #+#    #+#             */
/*   Updated: 2025/02/09 15:07:01 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	free_tiles(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < cub->scene.map.size.y)
		free(cub->minimap.tiles[i]);
	free(cub->minimap.tiles);
}
