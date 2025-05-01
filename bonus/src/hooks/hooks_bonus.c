/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcsilv <marcsilv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:33:35 by efinda            #+#    #+#             */
/*   Updated: 2025/05/01 13:03:24 by marcsilv         ###   ########.fr       */
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
	cub3D(cub);
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

static int	my_mlx_put_img_to_img_init(t_img *dst, t_img src, t_point crd,
		t_plane *dst_iter)
{
	if (!dst || crd.x < 0 || crd.x >= dst->width || crd.y < 0
		|| crd.y >= dst->height)
		return (1);
	if (crd.x + src.width > dst->width)
		src.width = dst->width - crd.x;
	if (crd.y + src.height > dst->height)
		src.height = dst->height - crd.y;
	*dst_iter = (t_plane){crd.x, crd.x, crd.y, crd.y};
	return (0);
}
void	my_mlx_put_gun(t_cub *cub, t_img *dst, t_img src, t_point crd)
{
	t_point	src_iter;
	t_plane	dst_iter;
	int		color;

	if (my_mlx_put_img_to_img_init(dst, src, crd, &dst_iter))
		return ;
	src_iter.y = -1;
	while (++src_iter.y < src.height)
	{
		src_iter.x = -1;
		dst_iter.x = dst_iter.x0;
		while (++src_iter.x < src.width)
		{
			color = my_mlx_get_pixel(src, src_iter.x, src_iter.y);
			if (color == TRANSPARENT || color == BLACK)
				color = my_mlx_get_pixel(cub->sprites.imgs[CLEAR], src_iter.x,
						src_iter.y);
			my_mlx_pixel_put(dst, (t_point) {dst_iter.x, dst_iter.y}, color);
			dst_iter.x++;
		}
		dst_iter.y++;
	}
}
void	update_shooting_animation(t_cub *cub)
{
	long	current_time;
	static int		i = 0;

	if (cub->sprites.idle)
		blit_image_alpha(cub->sprites.imgs[IDLE], &cub->img, cub->img.width / 2, (cub->img.height - cub->sprites.imgs[IDLE].height));
	else if (cub->sprites.shooting)
	{
		current_time = get_current_time();
		if (current_time - cub->sprites.last_frame_time >= 35)
		{
			cub->sprites.last_frame_time = current_time;
			if (cub->sprites.current_frame <= SHELL_08)
			{
				// cub->img = cub->player.imgs[cub->sprites.current_frame];
				my_mlx_put_gun(cub, &cub->img,
				cub->sprites.imgs[cub->sprites.current_frame],
				(t_point){cub->img.width / 2, cub->img.height
				- cub->sprites.imgs[cub->sprites.current_frame].height});
				i++;
				if (i % 2 == 0)
					cub->sprites.current_frame++;
			}
			else
			{
				cub->sprites.shooting = false;
				cub->sprites.idle = true;
				cub->sprites.current_frame = IDLE;
				my_mlx_put_gun(cub, &cub->img,
			cub->sprites.imgs[cub->sprites.current_frame],
			(t_point){cub->img.width / 2, cub->img.height
			- cub->sprites.imgs[cub->sprites.current_frame].height});
			}
		}
	}
}

int	my_mlx_mouse_click(int keycode, int x, int y, t_cub *cub)
{
	if (keycode == 1 && cub->sprites.idle)
	{
		if (--cub->sprites.ammo < 0)
			cub->sprites.ammo = 0;
		cub->sprites.idle = false;
		cub->sprites.shooting = true;
		cub->sprites.cur_frame_index = SHOOTING_01;
		cub->sprites.last_frame_time = get_current_time();
	}
	return (0);
}

int	my_mlx_loop_hook(t_cub *cub)
{
	my_mlx_mouse_motion(cub);
	// mlx_clear_window(cub->mlx, cub->win);
	update_shooting_animation(cub);

	// 	update_frame(&cub->img, &cub->sprites, 0);
	// player(cub);
	// funcao(cub, cub->minimap.cur);
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
