/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:33:35 by efinda            #+#    #+#             */
/*   Updated: 2025/02/15 01:24:13 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static int	my_mlx_close(t_cub *cub)
{
	int	i;

	i = -1;
	ft_mtxfree(&cub->scene.map.content);
	while (++i < 4)
		mlx_destroy_image(cub->mlx, cub->scene.textures[i].img.img);
	mlx_destroy_image(cub->mlx, cub->img.img);
	mlx_destroy_window(cub->mlx, cub->win);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	exit(0);
}

static int	my_mlx_key_press(int keycode, t_cub *cub)
{
	if (keycode == ESC)
		my_mlx_close(cub);
	else if (keycode == WKEY)
		move_player(cub, cub->player.pos, (t_plane){1, 0, 0, 0});
	else if (keycode == SKEY)
		move_player(cub, cub->player.pos, (t_plane){0, 1, 0, 0});
	else if (keycode == DKEY)
		move_player(cub, cub->player.pos, (t_plane){0, 0, 1, 0});
	else if (keycode == AKEY)
		move_player(cub, cub->player.pos, (t_plane){0, 0, 0, 1});
	else if (keycode == RIGHT)
		rotate_player(cub, 1);
	else if (keycode == LEFT)
		rotate_player(cub, 0);
	else
		return (0);
	cub3D(cub, -1);
	return (0);
}

void	my_mlx_hook(t_cub *cub)
{
	mlx_hook(cub->win, 2, 1L << 0, my_mlx_key_press, cub);
	mlx_hook(cub->win, 17, 1L << 17, my_mlx_close, cub);
}
