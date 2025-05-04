/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:06:04 by efinda            #+#    #+#             */
/*   Updated: 2025/05/04 12:34:42 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static void	bresenham_line_init(t_bresenham_line *line)
{
	line->dist.x = abs(line->crd.x - line->crd.x0);
	line->dist.y = -abs(line->crd.y - line->crd.y0);
	if (line->crd.x0 < line->crd.x)
		line->dir.x = 1;
	else
		line->dir.x = -1;
	if (line->crd.y0 < line->crd.y)
		line->dir.y = 1;
	else
		line->dir.y = -1;
	line->error = line->dist.x + line->dist.y;
}

void	bresenham_line(t_bresenham_line line)
{
	bresenham_line_init(&line);
	while (1)
	{
		my_mlx_pixel_put(line.img, line.crd.x0, line.crd.y0, line.color);
		if (line.crd.x0 == line.crd.x && line.crd.y0 == line.crd.y)
			break ;
		line.updated_error = 2 * line.error;
		if (line.updated_error >= line.dist.y)
		{
			line.error += line.dist.y;
			line.crd.x0 += line.dir.x;
		}
		if (line.updated_error <= line.dist.x)
		{
			line.error += line.dist.x;
			line.crd.y0 += line.dir.y;
		}
	}
}
