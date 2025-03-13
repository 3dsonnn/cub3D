/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:28:25 by efinda            #+#    #+#             */
/*   Updated: 2025/03/13 09:39:42 by efinda           ###   ########.fr       */
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

void	bresenham_circle(t_bresenham_circle circle)
{
    while (++circle.crd.x <= circle.crd.y)
    {
        // Draw horizontal lines for each y level using symmetry
        int y_pos = circle.center.y + circle.crd.y;
        int y_neg = circle.center.y - circle.crd.y;
        int x_left = circle.center.x - circle.crd.x;
        int x_right = circle.center.x + circle.crd.x;
        
        // Fill from x_left to x_right at y_pos
        for (int i = x_left; i <= x_right; i++)
                my_mlx_pixel_put(circle.img, i, y_pos, circle.color);

        // Fill from x_left to x_right at y_neg (if different from y_pos)
        if (y_neg != y_pos)
            for (int i = x_left; i <= x_right; i++)
                    my_mlx_pixel_put(circle.img, i, y_neg, circle.color);

        // For the swapped octants (when x and y are swapped)
        y_pos = circle.center.y + circle.crd.x;
        y_neg = circle.center.y - circle.crd.x;
        x_left = circle.center.x - circle.crd.y;
        x_right = circle.center.x + circle.crd.y;

        // Fill from x_left to x_right at y_pos
        for (int i = x_left; i <= x_right; i++)
                my_mlx_pixel_put(circle.img, i, y_pos, circle.color);

        // Fill from x_left to x_right at y_neg (if different)
        if (y_neg != y_pos)
            for (int i = x_left; i <= x_right; i++)
                    my_mlx_pixel_put(circle.img, i, y_neg, circle.color);

        // Update decision parameter
        if (circle.decision < 0)
            circle.decision += 4 * circle.crd.x + 6;
        else
        {
            circle.decision += 4 * (circle.crd.x - circle.crd.y) + 10;
            circle.crd.y--;
        }
    }
}
