/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 01:16:17 by efinda            #+#    #+#             */
/*   Updated: 2025/03/04 17:34:11 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

double	ft_normalizer(double angle)
{
    double  result;

    result = remainder(angle, (2 * M_PI));
    if (result < 0)
        result += (2 * M_PI);
    return (result);
}