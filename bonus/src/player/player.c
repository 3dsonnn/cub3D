/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcsilv <marcsilv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 08:54:06 by efinda            #+#    #+#             */
/*   Updated: 2025/04/16 20:42:01 by marcsilv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

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

static void	my_mlx_put_transparent(t_img *dst, t_img src, t_point crd, t_point xy, t_cub *cub)
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
			color = my_mlx_get_transparent_color(my_mlx_get_pixel(cub->img, xy.x, xy.y), my_mlx_get_pixel(cub->player.imgs[CARTIDGE], src_iter.x, src_iter.y), .5);
			my_mlx_pixel_put(dst, dst_iter.x, dst_iter.y, color);
			dst_iter.x++;
		}
		dst_iter.y++;
	}
}

void	put_ammo(t_cub *cub)
{
	int	x;
	int xis;

	x = 0;
	xis = 0;

	while (x < cub->player.ammo)
	{
		my_mlx_put_transparent(&cub->img, cub->player.imgs[CARTIDGE], (t_point){xis, 0}, (t_point){xis, 0}, cub);
		xis += (cub->player.imgs[CARTIDGE].width +10);
		x++;
	}
	x = 0;
	xis = 0;
	while (x < cub->player.ammo)
	{
		my_mlx_put_img_to_img(&cub->img, cub->player.imgs[CARTIDGE], (t_point){xis, 0}, 1);
		xis += (cub->player.imgs[CARTIDGE].width +10);
		x++;
	}
}

void	player(t_cub *cub)
{
	my_mlx_draw_ret_to_img(&cub->img, (t_point){10, cub->img.height - 40},
		(t_point){300, 30}, DARK_GRAY);
	my_mlx_draw_ret_to_img(&cub->img, (t_point){10, cub->img.height - 40},
		(t_point){((300 * cub->player.health.value) / 100), 30}, RED);
	my_mlx_put_img_to_img(&cub->img, cub->player.imgs[CROSSHAIR],
		(t_point){(cub->img.width - cub->player.imgs[CROSSHAIR].width) / 2,
		(cub->img.height - cub->player.imgs[CROSSHAIR].height) / 2}, 1);
	if (cub->player.idle)
		my_mlx_put_img_to_img(&cub->img, cub->player.imgs[IDLE],
			(t_point){cub->img.width / 2, (cub->img.height
				- cub->player.imgs[IDLE].height)}, 1);
	// put_ammo(cub);
}
