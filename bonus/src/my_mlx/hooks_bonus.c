/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:33:35 by efinda            #+#    #+#             */
/*   Updated: 2025/03/16 20:13:44 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static int	my_mlx_close(t_cub *cub)
{
	int	i;

	i = -1;
	free_tiles(&cub->minimap.tiles, -1, cub->scene.map.size.y);
	while (++i < 4)
		mlx_destroy_image(cub->mlx, cub->scene.textures[i].img.img);
	mlx_destroy_image(cub->mlx, cub->img.img);
	mlx_destroy_window(cub->mlx, cub->win);
	mlx_destroy_display(cub->mlx);
	free(cub->rays);
	free(cub->mlx);
	exit(0);
}

static	int	my_mlx_key_press(int keycode, t_cub *cub)
{
	if (keycode == ESC)
		my_mlx_close(cub);
	else if (keycode == WKEY)
		move_player(cub, 1, 0, cub->player.pos);
	else if (keycode == SKEY)
		move_player(cub, -1, 0, cub->player.pos);
	else if (keycode == DKEY)
		move_player(cub, 0, 1, cub->player.pos);
	else if (keycode == AKEY)
		move_player(cub, 0, -1, cub->player.pos);
	else if (keycode == RIGHT)
		rotate_player(cub, ROT);
	else if (keycode == LEFT)
		rotate_player(cub, -ROT);
	else if (keycode == ALT)
		alt(cub);
	else if (keycode == SPACE)
		space(cub);
	else
		return (0);
	cub3D(cub);
}

static	int	my_mlx_mouse_motion(t_cub *cub)
{
	t_point	crd;

    if (cub->hooks.alt)
		return (0);
	mlx_mouse_get_pos(cub->mlx, cub->win, &crd.x, &crd.y);
	if (crd.x != (int)(cub->img.width / 2))
	{
		if (crd.x < (int)(cub->img.width / 2))
			my_mlx_key_press(LEFT, cub);
		else
			my_mlx_key_press(RIGHT, cub);
		mlx_mouse_move(cub->mlx, cub->win, (int)(cub->img.width / 2), (int)(cub->img.height / 2));
	}
	return (0);
}

void	my_mlx_hook(t_cub *cub)
{
	mlx_hook(cub->win, 2, 1L << 0, my_mlx_key_press, cub);
	mlx_hook(cub->win, 17, 1L << 17, my_mlx_close, cub);
	mlx_loop_hook(cub->mlx, my_mlx_mouse_motion, cub);
}
