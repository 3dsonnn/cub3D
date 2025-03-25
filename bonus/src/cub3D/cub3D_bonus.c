/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:20:38 by efinda            #+#    #+#             */
/*   Updated: 2025/03/25 02:25:31 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

void	cub3D(t_cub *cub)
{
	get_rays(cub, -1);
	minimap(cub);
	player(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
}
