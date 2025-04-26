/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:24:28 by efinda            #+#    #+#             */
/*   Updated: 2025/04/26 14:38:45 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

void	open_door(t_cub *cub, t_tile *cur)
{
	cub->scene.map.door.cur_time = get_current_time();
	if (cur->left->id == 'D')
		cur->left->id = 'd';
	if (cur->right->id == 'D')
		cur->right->id = 'd';
	if (cur->up->id == 'D')
		cur->up->id = 'd';
	if (cur->down->id == 'D')
		cur->down->id = 'd';
}

static void	toggle_door(t_tile *tile)
{
	if (!tile)
		return ;
	if (tile->id == 'D')
		tile->id = 'd';
	else if (tile->id == 'd')
		tile->id = 'D';
}

void	open_or_close_door(t_tile *cur)
{
	toggle_door(cur->left);
	toggle_door(cur->right);
	toggle_door(cur->up);
	toggle_door(cur->down);
}

void	funcao(t_cub *cub, t_tile *cur)
{
	if (cur->left->id == 'D' || cur->right->id == 'D' || cur->down->id == 'D'
		|| cur->up->id == 'D')
	{
		my_mlx_put_img_to_img(&cub->img, cub->scene.map.door.key,
			(t_point){(cub->img.width / 2) - (cub->scene.map.door.key.width / 2),
			(cub->img.height / 2) + (cub->img.height / 3)}, 1);
		// my_mlx_put_img_to_img(&cub->img, cub->scene.rotated_key.img,
		// 	(t_point){(cub->img.width / 2) - (cub->scene.rotated_key.img.width
		// 		/ 2), (cub->img.height / 2)}, 1);
	}
	if (cub->scene.map.door.cur_time + 1500 <= get_current_time())
	{
		if (cub->minimap.cur->left->id == 'd')
			cub->minimap.cur->left->id = 'D';
		if (cub->minimap.cur->right->id == 'd')
			cub->minimap.cur->right->id = 'D';
		if (cub->minimap.cur->up->id == 'd')
			cub->minimap.cur->up->id = 'D';
		if (cub->minimap.cur->down->id == 'd')
			cub->minimap.cur->down->id = 'D';
		mlx_put_image_to_window(cub->mlx, cub->win, cub->img.img, 0, 0);
	}
}
