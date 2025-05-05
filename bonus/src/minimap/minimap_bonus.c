/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 22:59:10 by efinda            #+#    #+#             */
/*   Updated: 2025/05/04 13:35:39 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

void	minimap(t_cub *cub)
{
	paint_minimap(cub, cub->minimap.corners[TOPLEFT]);
	get_circle_img(&cub->minimap.circle, cub->minimap.img, (t_point){-1, -1});
	rotate_img(&cub->minimap.rotated, cub->minimap.circle, &cub->minimap.padded,
		-(cub->player.angle + cub->minimap.angle));
	blit_rotated_img(&cub->img, cub->minimap.rotated, (t_point){-30, -30});
}
