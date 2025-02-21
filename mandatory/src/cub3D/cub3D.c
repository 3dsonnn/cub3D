/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:20:38 by efinda            #+#    #+#             */
/*   Updated: 2025/02/21 17:53:51 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static	void	paint_ceiling_and_floor(t_cub *cub, int j)
{
	int	i;

	i = -1;
	while (++i < cub->img.height)
	{
		if (i < cub->img.height / 2)
			my_mlx_pixel_put(&cub->img, j, i, cub->scene.ceiling);
		else
			my_mlx_pixel_put(&cub->img, j, i, cub->scene.floor);
	}
}

static	void	paint_image(t_cub *cub, int i)
{
	while (++i < cub->img.width)
	{
		paint_ceiling_and_floor(cub, i);
	}
}

// void	render_wall(t_data *data, int x)
// {
// 	int	y;
// 	int	index;
// 	int	offset_x;
// 	int	offset_y;
// 	int	offset_index;

// 	if (data->rays[x].vertical_hit)
// 		offset_x = (int)data->rays[x].wall_hit_y % TILE_SIZE;
// 	else
// 		offset_x = (int)data->rays[x].wall_hit_x % TILE_SIZE;
// 	y = data->column[x].top_y;
// 	while (y < data->column[x].bottom_y)
// 	{
// 		offset_y = (y + data->column[x].dist_from_top) * \
// 					((double)TILE_SIZE / data->column[x].height);
// 		index = (y * data->main_img.line_length) + x;
// 		offset_index = offset_x + (offset_y * \
// 					data->imgs[data->column[x].facing_side].line_length);
// 		data->main_img.buffer[index] = \
// 			data->imgs[data->column[x].facing_side].buffer[offset_index];
// 		y++;
// 	}
// }

void	cub3D(t_cub *cub)
{
	//player(cub);
	//minimap(cub, -1, -1);
	get_rays(cub, -1);
	paint_image(cub, -1);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
}
