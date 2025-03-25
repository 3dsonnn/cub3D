/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_manipulation_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:34:02 by efinda            #+#    #+#             */
/*   Updated: 2025/03/24 14:07:21 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

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

void	my_mlx_put_img_to_img(t_img *dst, t_img src, t_point crd, int flag)
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
			if (!flag || color != TRANSPARENT)
				my_mlx_pixel_put(dst, dst_iter.x, dst_iter.y, color);
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
