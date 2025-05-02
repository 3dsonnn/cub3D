/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:33:35 by efinda            #+#    #+#             */
/*   Updated: 2025/05/02 02:55:18 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static int	my_mlx_close(t_cub *cub)
{
	int	i;

	i = -1;
	free_tiles(&cub->minimap.tiles, -1, cub->scene.map.size.y);
	while (++i < 4)
		my_mlx_destroy_img(cub->mlx, &cub->scene.textures[i].img);
	my_mlx_destroy_img(cub->mlx, &cub->img);
	mlx_destroy_window(cub->mlx, cub->win);
	mlx_do_key_autorepeaton(cub->mlx);
	mlx_destroy_display(cub->mlx);
	free(cub->rays);
	free(cub->mlx);
	exit(0);
}

static int	my_mlx_key_press(int keycode, t_cub *cub)
{
	if (keycode == ESC)
		my_mlx_close(cub);
	else if (keycode == WKEY || keycode == SKEY || keycode == AKEY
		|| keycode == DKEY)
	{
		if (move_player(cub, keycode))
			return (0);
	}
	else if (keycode == RIGHT || keycode == LEFT || keycode == UP
		|| keycode == DOWN)
	{
		if (rotate_player(cub, keycode))
			return (0);
	}
	else if (keycode == ALT || keycode == SPACE)
		alt_space(cub, keycode);
	else if (keycode == EKEY && is_door(cub->minimap.cur))
		open_or_close_door(cub->minimap.cur);
	else
		return (0);
	cub3d(cub);
	return (0);
}

static int	my_mlx_mouse_motion(t_cub *cub)
{
	static bool	flag = true;
	t_point		crd;

	if (cub->hooks.alt)
		return (0);
	mlx_mouse_get_pos(cub->mlx, cub->win, &crd.x, &crd.y);
	if (flag && abs(crd.x - HALF_WIDTH) > 10)
	{
		if (crd.x - HALF_WIDTH < 0)
			my_mlx_key_press(LEFT, cub);
		else
			my_mlx_key_press(RIGHT, cub);
		mlx_mouse_move(cub->mlx, cub->win, HALF_WIDTH, HALF_HEIGHT);
	}
	else if (!flag && abs(crd.y - HALF_HEIGHT) > 10)
	{
		if (crd.y - HALF_HEIGHT < 0)
			my_mlx_key_press(UP, cub);
		else
			my_mlx_key_press(DOWN, cub);
		mlx_mouse_move(cub->mlx, cub->win, HALF_WIDTH, HALF_HEIGHT);
	}
	flag = !flag;
	return (0);
}

int	my_mlx_loop_hook(t_cub *cub)
{
	my_mlx_mouse_motion(cub);
	if (cub->sprites.idle)
		put_shooting_animation(&cub->img, cub->sprites.imgs[IDLE],
			cub->sprites.imgs[CLEAR]);
	else if (cub->sprites.shooting)
		update_shooting_animation(&cub->img, &cub->sprites, 0);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
	return (0);
}

void	my_mlx_hook(t_cub *cub)
{
	mlx_hook(cub->win, 2, 1L << 0, my_mlx_key_press, cub);
	mlx_hook(cub->win, 17, 1L << 17, my_mlx_close, cub);
	mlx_hook(cub->win, 4, 1L << 2, my_mlx_mouse_click, cub);
	mlx_loop_hook(cub->mlx, my_mlx_loop_hook, cub);
}
