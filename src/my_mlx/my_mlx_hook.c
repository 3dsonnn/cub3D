/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:33:35 by efinda            #+#    #+#             */
/*   Updated: 2025/01/17 15:47:43 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static int	my_mlx_close(t_cub *cub)
{
	int	i;

	i = -1;
	while (++i < 4)
		mlx_destroy_image(cub->mlx, cub->scene.walls[i].img.img);
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
	else if (keycode == WKEY || keycode == UP)
	{
		printf("x0=%d\tx=%d\ty0=%d\ty=%d\n", cub->player.pos.x0, cub->player.pos.x, cub->player.pos.y0, cub->player.pos.y);
		if (cub->player.pos.y0 - cub->player.size.y <= cub->player.up->pos.y)
		{
			if (cub->player.up->id != '1')
			{
				cub->player.pos.y0 -= cub->player.size.y;
				cub->minimap.tiles[cub->player.i - 1][cub->player.j].id = 'E';
			}
		}
		else
			cub->player.pos.y0 -= cub->player.size.y;
	}
	else if (keycode == SKEY || keycode == DOWN)
	{
		printf("x0=%d\tx=%d\ty0=%d\ty=%d\n", cub->player.pos.x0, cub->player.pos.x, cub->player.pos.y0, cub->player.pos.y);
		if (cub->player.pos.y0 + cub->player.size.y >= cub->player.down->pos.y0)
		{
			if (cub->player.down->id != '1')
			{
				cub->player.pos.y0 += cub->player.size.y;
				cub->minimap.tiles[cub->player.i + 1][cub->player.j].id = 'E';
			}
		}
		else
			cub->player.pos.y0 += cub->player.size.y;
	}
	else if (keycode == DKEY || keycode == RIGHT)
	{
		printf("x0=%d\tx=%d\ty0=%d\ty=%d\n", cub->player.pos.x0, cub->player.pos.x, cub->player.pos.y0, cub->player.pos.y);
		if (cub->player.pos.x0 + cub->player.size.x >= cub->player.next->pos.x0)
		{
			if (cub->player.next->id != '1')
			{
				cub->player.pos.x0 += cub->player.size.x;
				cub->minimap.tiles[cub->player.i][cub->player.j + 1].id = 'E';
			}
		}
		else
			cub->player.pos.x0 += cub->player.size.x;
	}
	else if (keycode == AKEY || keycode == LEFT)
	{
		printf("x0=%d\tx=%d\ty0=%d\ty=%d\n", cub->player.pos.x0, cub->player.pos.x, cub->player.pos.y0, cub->player.pos.y);
		if (cub->player.pos.x0 - cub->player.size.x <= cub->player.prev->pos.x)
		{
			if (cub->player.prev->id != '1')
			{
				cub->player.pos.x0 += cub->player.size.x;
				cub->minimap.tiles[cub->player.i][cub->player.j - 1].id = 'E';
			}
		}
		else
			cub->player.pos.x0 += cub->player.size.x;
	}
	cub3D(cub);
	return (0);
}

static int	my_mlx_mouse_motion(int x, int y, t_cub *cub)
{
    (void)cub;
	printf("Mouse position: x=%d\ty=%d\n", x, y);
	return (0);
}

void	my_mlx_hook(t_cub *cub)
{
	mlx_hook(cub->win, 2, 1L << 0, my_mlx_key_press, cub);
	mlx_hook(cub->win, 17, 1L << 17, my_mlx_close, cub);
    mlx_hook(cub->win, 6, 1L << 6, my_mlx_mouse_motion, cub);
}
