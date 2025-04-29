/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcsilv <marcsilv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 10:22:21 by efinda            #+#    #+#             */
/*   Updated: 2025/04/29 12:46:08 by marcsilv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static void	draw_health_bar(t_cub *cub, t_point bar_size, t_point iter)
{
	t_point	active;

	my_mlx_draw_horizontal_lines_to_img(&cub->img, (t_point){20,
		(cub->img.height - (bar_size.y + 20))}, (t_point){bar_size.x,
		bar_size.y}, DARK_GRAY);
	if (cub->sprites.health.value <= 0)
		return ;
	active.x = (bar_size.x * cub->sprites.health.value) / 100;
	active.y = cub->img.height - (bar_size.y + 20);
	while (++iter.y < 30)
	{
		iter.x = -1;
		while (++iter.x < active.x)
		{
			if (!iter.x || iter.x == 1 || iter.x + 1 == active.x || iter.x
				+ 2 == active.x || !iter.y || iter.y == 1 || iter.y + 1 == 30
				|| iter.y + 2 == 30)
				my_mlx_pixel_put(&cub->img, 20 + iter.x, active.y + iter.y,
					WHITE);
			else
				my_mlx_pixel_put(&cub->img, 20 + iter.x, active.y + iter.y,
					RED);
		}
	}
}

t_img	cutout_circle_from_image(void *mlx, t_img src, int radius)
{
	t_img result;
	int diameter = radius * 2;
	result.width = diameter;
	result.height = diameter;
	result.img = mlx_new_image(mlx, diameter, diameter);
	result.addr = (int *)mlx_get_data_addr(result.img, &result.bpp, &result.line_len, &result.endian);
	result.line_len /= 4;

	int center_x = src.width / 2;
	int center_y = src.height / 2;

	for (int y = 0; y < diameter; ++y)
	{
		for (int x = 0; x < diameter; ++x)
		{
			int dx = x - radius;
			int dy = y - radius;
			if (dx * dx + dy * dy <= radius * radius)
			{
				int src_x = center_x + dx;
				int src_y = center_y + dy;
				int color = my_mlx_get_pixel(src, src_x, src_y);
				my_mlx_pixel_put(&result, x, y, color);
			}
			else
				my_mlx_pixel_put(&result, x, y, BLACK); // transparent
		}
	}

	return result;
}

void blit_image_alpha(t_img src, t_img *dst, int offset_x, int offset_y)
{
	for (int y = 0; y < src.height; y++)
	{
		for (int x = 0; x < src.width; x++)
		{
			int color = my_mlx_get_pixel(src, x, y);

			int alpha = (color >> 24) & 0xFF;
			if (color == BLACK || color == TRANSPARENT)
				continue;

			my_mlx_pixel_put(dst, x + offset_x, y + offset_y, color);
		}
	}
}
void	center_image(t_img src, t_img *dst)
{
	int offset_x = (dst->width - src.width) / 2;
	int offset_y = (dst->height - src.height) / 2;

	for (int y = 0; y < src.height; y++)
	{
		for (int x = 0; x < src.width; x++)
		{
			int color = my_mlx_get_pixel(src, x, y);
			my_mlx_pixel_put(dst, x + offset_x, y + offset_y, color);
		}
	}
}

void	rotate_image(t_img src, t_img *dst, float angle_degrees, t_cub *cub)
{
	t_img padded_src;
	padded_src.width = dst->width;
	padded_src.height = dst->height;
	padded_src.img = mlx_new_image(cub->mlx, padded_src.width, padded_src.height);
	padded_src.addr = (int *)mlx_get_data_addr(padded_src.img, &padded_src.bpp, &padded_src.line_len, &padded_src.endian);
	padded_src.line_len /= 4;

	for (int y = 0; y < padded_src.height; y++)
		for (int x = 0; x < padded_src.width; x++)
			my_mlx_pixel_put(&padded_src, x, y, BLACK);

	center_image(src, &padded_src);

	int cx = dst->width / 2;
	int cy = dst->height / 2;

	float angle_rad = angle_degrees;
	float cos_a = cos(angle_rad);
	float sin_a = sin(angle_rad);

	for (int y = 0; y < dst->height; ++y)
	{
		for (int x = 0; x < dst->width; ++x)
		{
			float xt = x - cx;
			float yt = y - cy;

			float src_x =  xt * cos_a + yt * sin_a;
			float src_y = -xt * sin_a + yt * cos_a;

			src_x += cx;
			src_y += cy;

			int nearest_x = (int)(src_x + 0.5f);
			int nearest_y = (int)(src_y + 0.5f);

			int color = my_mlx_get_pixel(padded_src, nearest_x, nearest_y);
			my_mlx_pixel_put(dst, x, y, color);
		}
	}

	mlx_destroy_image(cub->mlx, padded_src.img); // Cleanup
}

void draw_filled_triangle(void *mlx, void *win, int x, int y, int size, int color)
{
	int half_base = size / 2;
	int height = size;

	for (int i = 0; i < height; i++)
	{
		// Horizontal span at current row i
		int row_width = (int)((float)i / height * half_base);

		for (int j = -row_width; j <= row_width; j++)
		{
			int draw_x = x + j;
			int draw_y = y + i;
			mlx_pixel_put(mlx, win, draw_x, draw_y, color);
		}
	}
}

void	player(t_cub *cub)
{
	int	plus;

	if (cub->scene.map.start == 'N' || cub->scene.map.start == 'S')
		plus = 90;
	if (cub->scene.map.start == 'W' || cub->scene.map.start == 'E')
		plus = 270;
	t_img	cut = cutout_circle_from_image(cub->mlx, cub->minimap.img, 98);
	t_img rotated;
	// blit_image_alpha(circle, &cub->img, 10, 10);
	rotate_image(cut, &rotated, -(cub->player.angle + plus * (M_PI / 180)), cub);
	blit_image_alpha(rotated, &cub->img, 10, 10);
	// draw_health_bar(cub, (t_point){300, 30}, (t_point){-1, -1});
	// my_mlx_put_img_to_img(&cub->img, cub->sprites.imgs[CROSSHAIR],
	// 	(t_point){(cub->img.width - cub->sprites.imgs[CROSSHAIR].width) / 2,
	// 	(cub->img.height - cub->sprites.imgs[CROSSHAIR].height) / 2}, 1);
}
