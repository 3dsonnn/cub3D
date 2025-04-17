/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_get_pixel.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:30:24 by efinda            #+#    #+#             */
/*   Updated: 2025/04/16 23:45:16 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/my_mlx.h"

inline int	my_mlx_get_pixel(t_img img, int x, int y)
{
	if (!img.addr || x < 0 || x >= img.width || y < 0 || y >= img.height)
		return (TRANSPARENT);
	return (*(img.addr + y * img.line_len + x));
}
