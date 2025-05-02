/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_put_img_to_img.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 09:45:56 by efinda            #+#    #+#             */
/*   Updated: 2025/05/02 03:11:14 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/my_mlx_bonus.h"

static int	my_mlx_put_img_to_img_init(t_img_to_img *base, t_point *limits,
		t_point *iter)
{
	if (!base->dst || base->dst_point.x < 0
		|| base->dst_point.x >= base->dst->width || base->dst_point.y < 0
		|| base->dst_point.y >= base->dst->height)
		return (1);
	if (base->src_point.x < 0 || base->src_point.x >= base->src.width
		|| base->src_point.y < 0 || base->src_point.y >= base->src.height)
		return (1);
	if (base->size.x <= 0 || base->size.y <= 0)
		return (1);
	if (base->src_point.x + base->size.x > base->src.width)
		base->size.x = base->src.width - base->src_point.x;
	if (base->src_point.y + base->size.y > base->src.height)
		base->size.y = base->src.height - base->src_point.y;
	if (base->dst_point.x + base->size.x > base->dst->width)
		base->size.x = base->dst->width - base->dst_point.x;
	if (base->dst_point.y + base->size.y > base->dst->height)
		base->size.y = base->dst->height - base->dst_point.y;
	*limits = (t_point){.x = base->src_point.x + base->size.x,
		.y = base->src_point.y + base->size.y};
	*iter = (t_point){base->src_point.x - 1, base->src_point.y - 1};
	return (0);
}

void	my_mlx_put_img_to_img_get_color(t_img_to_img *base, int *color, int x,
		int y)
{
	if (base->color_aux != (int)TRANSPARENT)
		*color = base->color_aux;
	else if (base->aux)
		*color = my_mlx_get_pixel(*base->aux, x, y);
}

void	my_mlx_put_img_to_img(t_img_to_img base)
{
	t_point	iter;
	t_point	limits;
	int		color;

	if (my_mlx_put_img_to_img_init(&base, &limits, &iter))
		return ;
	while (++iter.y < limits.y)
	{
		iter.x = base.src_point.x - 1;
		while (++iter.x < limits.x)
		{
			color = my_mlx_get_pixel(base.src, iter.x, iter.y);
			if (base.filter && color == (int)TRANSPARENT)
			{
				if (base.skip)
					continue ;
				my_mlx_put_img_to_img_get_color(&base, &color, iter.x, iter.y);
			}
			my_mlx_pixel_put(base.dst, base.dst_point.x + (iter.x
					- base.src_point.x), base.dst_point.y + (iter.y
					- base.src_point.y), color);
		}
	}
}
