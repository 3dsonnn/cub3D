/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_resize_img_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:10:15 by efinda            #+#    #+#             */
/*   Updated: 2025/04/01 18:17:32 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/my_mlx_bonus.h"

static void	fill_img(t_img *src, t_img *dst, int x, int y)
{
	t_point	offset;
	int		pixel;

	while (++y < dst->height)
	{
		x = -1;
		while (++x < dst->width)
		{
			offset.x = ft_map(x, (int[]){0, dst->width}, (int[]){0, src->width});
			offset.y = ft_map(y, (int[]){0, dst->height}, (int[]){0,
					src->height});
			pixel = my_mlx_get_pixel(*src, offset.x, offset.y);
			my_mlx_pixel_put(dst, x, y, pixel);
		}
	}
}

void	my_mlx_resize_img(void *mlx, t_img *img, t_point size)
{
	t_img	new;

	if (!mlx || size.x <= 0 || size.y <= 0 || (img->width == size.x
			&& img->height == size.y))
		return ;
	my_mlx_init_img(&new);
	my_mlx_new_img(mlx, &new, size);
	if (!new.img)
		return ;
	my_mlx_get_data_addr(&new);
	if (!new.addr)
	{
		my_mlx_destroy_img(mlx, &new);
		return ;
	}
	fill_img(img, &new, -1, -1);
	my_mlx_destroy_img(mlx, img);
	*img = new;
}
