/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcsilv <marcsilv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 10:22:21 by efinda            #+#    #+#             */
/*   Updated: 2025/04/28 18:32:50 by marcsilv         ###   ########.fr       */
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
			if (color == BLACK)
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

void rotate_image(t_img src, t_img *dst, float angle_degrees, t_cub *cub)
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
t_img create_circle_image(void *mlx, int radius, int color)
{
	t_img circle_img;
	int diameter = radius * 2;

	circle_img.width = diameter;
	circle_img.height = diameter;
	circle_img.img = mlx_new_image(mlx, diameter, diameter);
	circle_img.addr = (int *)mlx_get_data_addr(circle_img.img, &circle_img.bpp, &circle_img.line_len, &circle_img.endian);
	circle_img.line_len /= 4;

	for (int y = 0; y < diameter; y++)
	{
		for (int x = 0; x < diameter; x++)
		{
			int dx = x - radius;
			int dy = y - radius;
			if (dx * dx + dy * dy <= radius * radius)
				my_mlx_pixel_put(&circle_img, x, y, color);
			else
				my_mlx_pixel_put(&circle_img, x, y, BLACK); // Transparent or black
		}
	}

	return circle_img;
}

t_img create_triangle_image(void *mlx, int size, int color)
{
	t_img img;

	img.width = size;
	img.height = size;
	img.img = mlx_new_image(mlx, size, size);
	img.addr = (int *)mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	img.line_len /= 4;

	float ax = size / 2.0f;
	float ay = 0;
	float bx = 0;
	float by = size - 1;
	float cx = size - 1;
	float cy = size - 1;

	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			float w0 = (bx - ax) * (y - ay) - (by - ay) * (x - ax);
			float w1 = (cx - bx) * (y - by) - (cy - by) * (x - bx);
			float w2 = (ax - cx) * (y - cy) - (ay - cy) * (x - cx);
			if ((w0 >= 0 && w1 >= 0 && w2 >= 0) || (w0 <= 0 && w1 <= 0 && w2 <= 0))
			{
				int rgba = (0xFF << 24) | (color & 0x00FFFFFF);
				my_mlx_pixel_put(&img, x, y, rgba);
			}
			else
				my_mlx_pixel_put(&img, x, y, 0x00000000);
		}
	}

	return img;
}

void	player(t_cub *cub)
{
	int	plus;

	if (cub->scene.map.start == 'N' || cub->scene.map.start == 'S')
		plus = 90;
	if (cub->scene.map.start == 'W' || cub->scene.map.start == 'E')
		plus = 270;
	my_mlx_put_img_to_img(&cub->img, cub->sprites.imgs[CROSSHAIR],
		(t_point){(cub->img.width - cub->sprites.imgs[CROSSHAIR].width) / 2,
		(cub->img.height - cub->sprites.imgs[CROSSHAIR].height) / 2}, 1);
	t_img	cut = cutout_circle_from_image(cub->mlx, cub->minimap.img, 98);
	// my_mlx_put_img_to_img(&cub->img, cut, (t_point){10,10}, 1);
	// t_img circle = create_circle_image(cub->mlx, 101, WHITE);
	// my_mlx_put_img_to_img(&cub->img, circle, (t_point){10, 10}, 1);
	t_img rotated;
	// blit_image_alpha(circle, &cub->img, 10, 10);
	rotate_image(cut, &rotated, cub->player.angle + plus * (M_PI / 180), cub);
	t_img triangle = create_triangle_image(cub->mlx, 12, YELLOW);
	blit_image_alpha(rotated, &cub->img, 13, 13);
	blit_image_alpha(triangle, &cub->img, 13 + (98 + 12  / 2), 13 + 12 / 2 + (98 ));
}
