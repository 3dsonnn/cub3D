/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 08:59:36 by efinda            #+#    #+#             */
/*   Updated: 2025/03/08 07:20:40 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

inline void    init_rays(t_cub *cub)
{
    cub->rays = (t_ray *)ft_calloc(cub->img.width, sizeof(t_ray));
    if (!cub->rays)
        my_mlx_free(cub, "Failed to allocate memory for rays", (t_plane){-1, 4, 1, 1});
    cub->ppd = (cub->img.width / 2) / tan(FOV / 2);
}
