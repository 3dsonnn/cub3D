/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_get_transparent_color_bonus.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:15:04 by efinda            #+#    #+#             */
/*   Updated: 2025/04/01 17:20:42 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/my_mlx_bonus.h"

int	my_mlx_get_transparent_color(int back, int fore, double level)
{
	int	rgb[3];
	int	back_rgb[3];
	int	fore_rgb[3];

	my_mlx_get_rgb_values(back, back_rgb);
	my_mlx_get_rgb_values(fore, fore_rgb);
	rgb[0] = (int)((fore_rgb[0] * level) + (back_rgb[0] * (1 - level)));
	rgb[1] = (int)((fore_rgb[1] * level) + (back_rgb[1] * (1 - level)));
	rgb[2] = (int)((fore_rgb[2] * level) + (back_rgb[2] * (1 - level)));
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}
