/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:03:40 by efinda            #+#    #+#             */
/*   Updated: 2025/01/15 12:12:55 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void    all_free(t_cub *cub, int i)
{
	free(cub->mlx);
	mlx_destroy_image(cub->mlx, cub->img.img);
	mlx_destroy_window(cub->mlx, cub->win);
	mlx_destroy_display(cub->mlx);
    ft_strfree(&cub->scene.tmp);
    ft_strfree(&cub->scene.line);
    ft_strfree(&cub->scene.elements);
    free_rows(&cub->scene.map.head);
    ft_mtxfree(&cub->scene.map.content);
	while (++i < 4)
		mlx_destroy_image(cub->mlx, cub->scene.walls[i].img.img);
    i = -1;
    while (++i < 4)
        ft_strfree(&cub->scene.walls[i].path);
}
