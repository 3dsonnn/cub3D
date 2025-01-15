/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:20:38 by efinda            #+#    #+#             */
/*   Updated: 2025/01/15 11:37:44 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	my_mlx_new_image(t_cub *cub)
{
	int	block_height;
	int	block_width;
	int	j;
	int	i;
	int	start_x;
	int	start_y;
	int	draw_y;
	int	draw_x;

	block_height = HEIGHT / cub->scene.map.size.y;
	block_width = WIDTH / cub->scene.map.size.x;
	j = 0;
	while (j < cub->scene.map.size.y)
	{
		i = 0;
		while (i < cub->scene.map.size.x)
		{
			start_x = i * block_width;
			start_y = j * block_height;
			if (start_x >= WIDTH || start_y >= HEIGHT)
			{
				i++;
				continue ;
			}
			if (cub->scene.map.content[j][i] == '1')
			{
				draw_y = start_y;
				while (draw_y < start_y + block_height && draw_y < HEIGHT)
				{
					draw_x = start_x;
					while (draw_x < start_x + block_width && draw_x < WIDTH)
					{
						my_mlx_pixel_put(&cub->img, draw_x, draw_y, 0x0000FF);
						draw_x++;
					}
					draw_y++;
				}
			}
			else if (cub->scene.map.content[j][i] == '0'
				|| cub->scene.map.content[j][i] == cub->scene.map.start)
			{
				if (cub->scene.map.content[j][i] == cub->scene.map.start)
				{
					if (!cub->player.y)
						cub->player.y = start_y;
					if (!cub->player.x)
						cub->player.x = start_x;
				}
				draw_y = start_y;
				while (draw_y < start_y + block_height && draw_y < HEIGHT)
				{
					draw_x = start_x;
					while (draw_x < start_x + block_width && draw_x < WIDTH)
					{
						my_mlx_pixel_put(&cub->img, draw_x, draw_y, 0xD3D3D3);
						draw_x++;
					}
					draw_y++;
				}
			}
			else if (cub->scene.map.content[j][i] == ' ')
			{
				draw_y = start_y;
				while (draw_y < start_y + block_height && draw_y < HEIGHT)
				{
					draw_x = start_x;
					while (draw_x < start_x + block_width && draw_x < WIDTH)
					{
						my_mlx_pixel_put(&cub->img, draw_x, draw_y, 0xFFFFFF);
						draw_x++;
					}
					draw_y++;
				}
			}
			i++;
		}
		j++;
	}
}

void	draw_player(t_cub *cub)
{
	int	x;
	int	y;

	y = cub->player.y + HEIGHT / cub->scene.map.size.y / 2;
	printf("Player position: %d %d\n", cub->player.x, cub->player.y);
	while (cub->player.y < --y)
	{
		x = cub->player.x + WIDTH / cub->scene.map.size.x / 2;
		while (x-- > cub->player.x)
			my_mlx_pixel_put(&cub->img, x, y, 0xFF0000);
	}
}

void	display(t_cub *cub)
{
	mlx_clear_window(cub->mlx, cub->win);
	my_mlx_new_image(cub);
	draw_player(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
}

void	cub3D(t_cub *cub)
{
    display(cub);
}