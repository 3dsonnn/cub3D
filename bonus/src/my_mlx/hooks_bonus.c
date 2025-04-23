/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcsilv <marcsilv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:33:35 by efinda            #+#    #+#             */
/*   Updated: 2025/04/23 19:08:14 by marcsilv         ###   ########.fr       */
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

// void	toggle_door(t_tile *tile)
// {
// 	if (tile->id == 'D')
// 		tile->id = 'd';
// 	else if (tile->id == 'd')
// 		tile->id = 'D';
// }
// void	open_or_close_door(t_cub *cub)
// {
// 	toggle_door(cub->minimap.cur->left);
// 	toggle_door(cub->minimap.cur->right);
// 	toggle_door(cub->minimap.cur->up);
// 	toggle_door(cub->minimap.cur->down);
// }

void	open_door(t_cub *cub)
{
	cub->cur_time = get_current_time();
	if (cub->minimap.cur->left->id == 'D')
		cub->minimap.cur->left->id = 'd';
	if (cub->minimap.cur->right->id == 'D')
		cub->minimap.cur->right->id = 'd';
	if (cub->minimap.cur->up->id == 'D')
		cub->minimap.cur->up->id = 'd';
	if (cub->minimap.cur->down->id == 'D')
		cub->minimap.cur->down->id = 'd';
}

static int	my_mlx_key_press(int keycode, t_cub *cub)
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
	else if ((keycode == E_KEY)
		&& ((cub->minimap.cur->left->id == 'D'
		|| cub->minimap.cur->right->id == 'D'
		|| cub->minimap.cur->down->id == 'D'
		|| cub->minimap.cur->up->id == 'D')))
		open_door(cub);
	else
		return (0);
	cub3D(cub);
}

static int	my_mlx_mouse_motion(t_cub *cub)
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
		mlx_mouse_move(cub->mlx, cub->win, (int)(cub->img.width / 2),
			(int)(cub->img.height / 2));
	}
	return (0);
}

int	mouse_hook(int keycode, int x, int y, t_cub *cub)
{
	if (keycode == 1 && cub->player.idle)
	{
		if (cub->player.ammo-- < 0)
			cub->player.ammo = 0;
		cub->player.idle = false;
		cub->player.shooting = true;
		cub->player.current_frame = SHOOTING_01;
		cub->player.last_frame_time = get_current_time();
	}
	return (0);
}

void	update_shooting_animation(t_cub *cub)
{
	long	current_time;
	static int		i = 0;

	current_time = get_current_time();
	if (current_time - cub->player.last_frame_time >= 35)
	{
		cub->player.last_frame_time = current_time;
		if (cub->player.current_frame <= SHELL_08)
		{
			// cub->img = cub->player.imgs[cub->player.current_frame];
			my_mlx_put_gun(cub, &cub->img,
				cub->player.imgs[cub->player.current_frame],
				(t_point){cub->img.width / 2, cub->img.height
				- cub->player.imgs[cub->player.current_frame].height});
			i++;
			if (i % 2 == 0)
				cub->player.current_frame++;
		}
		else
		{
			cub->player.shooting = false;
			cub->player.idle = true;
			cub->player.current_frame = IDLE;
			my_mlx_put_gun(cub, &cub->img,
			cub->player.imgs[cub->player.current_frame],
			(t_point){cub->img.width / 2, cub->img.height
			- cub->player.imgs[cub->player.current_frame].height});
		}
	}
}

void	fn(t_cub *cub, t_tile *tile)
{
	ft_printf("left: %c, right: %c, down: %c, up: %c\n", tile->left->id, tile->right->id, tile->down->id, tile->up->id);
	if (tile->left->id == 'D' || tile->right->id == 'D' || tile->down->id == 'D' || tile->up->id == 'D')
		my_mlx_put_img_to_img(&cub->img, cub->scene.e_key.img, (t_point){(cub->img.width / 2) - (cub->scene.e_key.img.width / 2), (cub->img.height / 2)+(cub->img.height / 3)}, 1);
	
	if (cub->cur_time + 1500 <= get_current_time())
	{
		if (cub->minimap.cur->left->id == 'd')
			cub->minimap.cur->left->id = 'D';
		if (cub->minimap.cur->right->id == 'd')
			cub->minimap.cur->right->id = 'D';
		if (cub->minimap.cur->up->id == 'd')
			cub->minimap.cur->up->id = 'D';
		if (cub->minimap.cur->down->id == 'd')
			cub->minimap.cur->down->id = 'D';
		cub3D(cub);
	}
}
// int lerp_color(int color_a, int color_b, float t)
// {
// 	t_RGB rgb1 = get_RGB(color_a);
// 	t_RGB rgb2 = get_RGB(color_b);

// 	int r = rgb1.r + (rgb2.r - rgb1.r) * t;
// 	int g = rgb1.g + (rgb2.g - rgb1.g) * t;
// 	int b = rgb1.b + (rgb2.b - rgb1.b) * t;

// 	return ((r << 16) | (g << 8) | b);
// }

// #include <stdio.h>

int	render_frame(t_cub *cub)
{
	my_mlx_mouse_motion(cub);
	mlx_clear_window(cub->mlx, cub->win);
	if (cub->player.shooting)
		update_shooting_animation(cub);
	player(cub);
	fn(cub, cub->minimap.cur);
	
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
	return (0);
}

void	my_mlx_hook(t_cub *cub)
{
	mlx_hook(cub->win, 2, 1L << 0, my_mlx_key_press, cub);
	mlx_hook(cub->win, 17, 1L << 17, my_mlx_close, cub);
	mlx_hook(cub->win, 4, 1L << 2, mouse_hook, cub);
	// mlx_loop_hook(cub->mlx, my_mlx_mouse_motion, cub);
	mlx_loop_hook(cub->mlx, render_frame, cub);
}
