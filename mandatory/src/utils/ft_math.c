/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 02:05:24 by efinda            #+#    #+#             */
/*   Updated: 2025/03/09 02:42:09 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

double	ft_normalizer(double angle)
{
	double	result;

	result = remainder(angle, (2 * M_PI));
	if (result < 0)
		result += (2 * M_PI);
	return (result);
}
