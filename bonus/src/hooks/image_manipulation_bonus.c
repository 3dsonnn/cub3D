/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_manipulation_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:34:02 by efinda            #+#    #+#             */
/*   Updated: 2025/04/01 17:23:02 by efinda           ###   ########.fr       */
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

void	my_mlx_draw_horizontal_lines_to_img(t_img *img, t_point crd, t_point size, int color)
{
	t_point	iter;

	iter = (t_point){.x = -1, .y = -1};
	if (!img || crd.x < 0 || crd.x > img->width || crd.y < 0
		|| crd.y > img->height || size.x <= 0 || size.y <= 0)
		return ;
	if (crd.x + size.x > img->width)
		size.x = img->width - crd.x;
	if (crd.y + size.y > img->height)
		size.y = img->height - crd.y;
	while (++iter.y < size.y)
	{
		iter.x = -1;
		while (++iter.x < size.x)
			my_mlx_pixel_put(img, crd.x + iter.x, crd.y + iter.y, color);
	}
}
