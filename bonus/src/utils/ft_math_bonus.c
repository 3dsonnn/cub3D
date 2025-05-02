/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 01:16:17 by efinda            #+#    #+#             */
/*   Updated: 2025/04/30 18:09:56 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

double	ft_normalizer(double angle)
{
	double	result;

	result = remainder(angle, (2 * M_PI));
	if (result < 0)
		result += (2 * M_PI);
	return (result);
}

float	ft_clamp(float value, float min, float max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

int	ft_map(int old_value, int old_limits[2], int new_limits[2])
{
	double	old_range;
	double	new_range;
	int		old_pos_range;

	new_range = new_limits[1] - new_limits[0];
	old_pos_range = old_value - old_limits[0];
	old_range = old_limits[1] - old_limits[0];
	if (!old_range)
		return (new_limits[0]);
	return ((int)(((new_range * old_pos_range) / old_range) + new_limits[0]));
}

unsigned long long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
