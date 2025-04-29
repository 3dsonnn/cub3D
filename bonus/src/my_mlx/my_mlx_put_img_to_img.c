/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_put_img_to_img.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 09:45:56 by efinda            #+#    #+#             */
/*   Updated: 2025/04/27 11:51:18 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/my_mlx_bonus.h"

static int	my_mlx_put_img_to_img_init(t_img_to_img *base, t_plane *limits)
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
	*limits = (t_plane){.x0 = base->src_point.x, .x = base->src_point.x
		+ base->size.x, .y0 = base->src_point.y, .y = base->src_point.y
		+ base->size.y};
	return (0);
}

void	my_mlx_put_img_to_img(t_img_to_img base)
{
	t_plane	limits;

	if (my_mlx_put_img_to_img_init(&base, &limits))
		return ;
	while (limits.y0 < limits.y)
	{
		limits.x0 = base.src_point.x;
		while (limits.x0 < limits.x)
		{
			base.color = my_mlx_get_pixel(base.src, limits.x0, limits.y0);
			if (base.filter && base.color == TRANSPARENT)
			{
				if (base.color_aux != TRANSPARENT)
					base.color = base.color_aux;
				else if (base.aux)
					base.color = my_mlx_get_pixel(*base.aux, limits.x0, limits.y0);
			}
			my_mlx_pixel_put(base.dst, base.dst_point.x + limits.x0,
				base.dst_point.y + limits.y0, base.color);
			limits.x0++;
		}
		limits.y0++;
	}
}
