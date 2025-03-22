/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_aux_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:37:22 by efinda            #+#    #+#             */
/*   Updated: 2025/03/22 01:51:20 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

void	my_mlx_put_img_to_img(t_img *dst, t_img src, int x, int y)
{
	t_point	src_iter;
	t_plane	dst_iter;

	if (!dst || x < 0 || x >= dst->width || y < 0 || y >= dst->height)
		return ;
	dst_iter = (t_plane){x, x, y, y};
	src_iter.y = -1;
	while (++src_iter.y < src.height)
	{
		src_iter.x = -1;
		dst_iter.x = dst_iter.x0;
		while (++src_iter.x < src.width)
		{
			my_mlx_pixel_put(dst, dst_iter.x, dst_iter.y, my_mlx_get_pixel(src,
					src_iter.x, src_iter.y));
			dst_iter.x++;
		}
		dst_iter.y++;
	}
}

static void	fill_img(t_img src, t_img *dst, int x, int y)
{
	t_point	offset;
	int		pixel;

	while (++y < dst->height)
	{
		x = -1;
		while (++x < dst->width)
		{
			offset.x = ft_map(x, (int[]){0, dst->width}, (int[]){0, src.width});
			offset.y = ft_map(y, (int[]){0, dst->height}, (int[]){0,
					src.height});
			pixel = my_mlx_get_pixel(src, offset.x, offset.y);
			my_mlx_pixel_put(dst, x, y, pixel);
		}
	}
}

t_img	my_mlx_resize_img(void *mlx, t_img img, t_point new_size)
{
	t_img	res;

	if (new_size.x <= 0 || new_size.y <= 0 || (img.width == new_size.x
			&& img.height == new_size.y))
		return (img);
	res.img = mlx_new_image(mlx, new_size.x, new_size.y);
	if (!res.img)
		return (img);
	res.addr = (int *)mlx_get_data_addr(res.img, &res.bpp, &res.line_len,
			&res.endian);
	if (!res.addr)
	{
		mlx_destroy_image(mlx, res.img);
		return (img);
	}
	res.line_len /= 4;
	res.width = new_size.x;
	res.height = new_size.y;
	fill_img(img, &res, -1, -1);
	mlx_destroy_image(mlx, img.img);
	return (res);
}
