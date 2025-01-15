/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:33:35 by efinda            #+#    #+#             */
/*   Updated: 2025/01/15 02:17:58 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static  int mlx_close(t_cub *cub)
{
    int i;

    i = -1;
    while (++i < 4)
        mlx_destroy_image(cub->mlx, cub->scene.walls[i].img.img);
    mlx_destroy_image(cub->mlx, cub->img.img);
    mlx_destroy_window(cub->mlx, cub->win);
    mlx_destroy_display(cub->mlx);
    free(cub->mlx);
    exit(0);
}

static  int mlx_key_press(int keycode, t_cub *cub)
{
    if (keycode == ESC)
        mlx_close(cub);
    if (keycode == WKEY)
        printf("W\n");
    if (keycode == AKEY)
        printf("A\n");
    if (keycode == SKEY)
        printf("S\n");
    if (keycode == DKEY)
        printf("D\n");    
    return (0);
}

static  int mlx_key_release(int keycode, t_cub *cub)
{
    if (keycode == ESC)
        mlx_close(cub);
    return (0);
}

void	my_mlx_hook(t_cub *cub)
{
    mlx_hook(cub->win, 2, 1L << 0, mlx_key_press, cub);
    mlx_hook(cub->win, 3, 1L << 1, mlx_key_release, cub);
    mlx_hook(cub->win, 17, 1L << 17, mlx_close, cub);
}
