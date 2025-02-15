/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:20:38 by efinda            #+#    #+#             */
/*   Updated: 2025/02/13 15:13:44 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	cub3D(t_cub *cub, int i)
{
	//player(cub);
	//minimap(cub, -1, -1);
	while (++i < cub->img.width)
	{

	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
}
