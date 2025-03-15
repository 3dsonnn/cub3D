/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 22:57:45 by efinda            #+#    #+#             */
/*   Updated: 2025/03/15 07:06:24 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

int blend_colors(int bg, int fg, float alpha)
{
    int r, g, b;
    
    // Extract RGB components
    int bg_r = (bg >> 16) & 0xFF;
    int bg_g = (bg >> 8) & 0xFF;
    int bg_b = bg & 0xFF;

    int fg_r = (fg >> 16) & 0xFF;
    int fg_g = (fg >> 8) & 0xFF;
    int fg_b = fg & 0xFF;

    // Apply blending formula
    r = (int)((fg_r * alpha) + (bg_r * (1 - alpha)));
    g = (int)((fg_g * alpha) + (bg_g * (1 - alpha)));
    b = (int)((fg_b * alpha) + (bg_b * (1 - alpha)));

    // Reassemble blended color
    return (r << 16) | (g << 8) | b;
}

void	paint_minimap_tile(t_cub *cub, int i, int j, int color)
{
	int	x0;
	int	x;
	int	y0;
	int	y;

	y0 = i * cub->minimap.tilesize + 10;
	x = (j + 1) * cub->minimap.tilesize + 10;
	y = (i + 1) * cub->minimap.tilesize + 10;
	while (y0 < y)
	{
		x0 = j * cub->minimap.tilesize + 10;
		while (x0 < x)
		{
			if (x0 == j * cub->minimap.tilesize + 10 || x0 == x - 1 || y0 == i
				* cub->minimap.tilesize + 10 || y0 == y - 1)
				my_mlx_pixel_put(&cub->img, x0, y0, WHITE);
			else
				my_mlx_pixel_put(&cub->img, x0, y0, blend_colors(color, my_mlx_get_pixel(&cub->img, x0, y0), 0.5));
			x0++;
		}
		y0++;
	}
}

void	paint_obx(t_cub *cub, t_tile *topleft, t_point *minip)
{
	t_tile	*tmp;
	t_point	pos;

	pos = (t_point){-1, -1};
	while (++(pos.y) < cub->minimap.bounds.y + 1)
	{
		pos.x = -1;
		tmp = topleft;
		while (++(pos.x) < cub->minimap.bounds.x + 1)
		{
			if (tmp->id == 'C')
			{
				minip->x = pos.x * cub->minimap.tilesize + 10;
				minip->y = pos.y * cub->minimap.tilesize + 10;
			}
			if (tmp->id == ' ')
				;
			else
				paint_minimap_tile(cub, pos.y, pos.x, tmp->color);
			tmp = tmp->right;
		}
		topleft = topleft->down;
	}
}
