/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:28:25 by efinda            #+#    #+#             */
/*   Updated: 2025/03/13 06:43:08 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static void	init_line(t_bresenham_line *line)
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
	init_line(&line);
	while (1)
	{
		my_mlx_pixel_put(line.img, line.crd.x0, line.crd.y0, GREEN);
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

void	bresenham_circle(t_img *img, int cx, int cy, int radius)
{
	int x = -1;
    int y = radius;
    int decision = 3 - 2 * radius;

    while (++x <= y)
    {
        // Draw horizontal lines for each y level using symmetry
        int y_pos = cy + y;
        int y_neg = cy - y;
        int x_left = cx - x;
        int x_right = cx + x;
        
        // Fill from x_left to x_right at y_pos
        for (int i = x_left; i <= x_right; i++)
                my_mlx_pixel_put(img, i, y_pos, RED);

        // Fill from x_left to x_right at y_neg (if different from y_pos)
        if (y_neg != y_pos)
            for (int i = x_left; i <= x_right; i++)
                    my_mlx_pixel_put(img, i, y_neg, RED);

        // For the swapped octants (when x and y are swapped)
        y_pos = cy + x;
        y_neg = cy - x;
        x_left = cx - y;
        x_right = cx + y;

        // Fill from x_left to x_right at y_pos
        for (int i = x_left; i <= x_right; i++)
                my_mlx_pixel_put(img, i, y_pos, RED);

        // Fill from x_left to x_right at y_neg (if different)
        if (y_neg != y_pos)
            for (int i = x_left; i <= x_right; i++)
                    my_mlx_pixel_put(img, i, y_neg, RED);

        // Update decision parameter
        if (decision < 0)
            decision += 4 * x + 6;
        else
        {
            decision += 4 * (x - y) + 10;
            y--;
        }
    }
}
