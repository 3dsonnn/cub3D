/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcsilv <marcsilv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 08:54:06 by efinda            #+#    #+#             */
/*   Updated: 2025/03/23 18:29:24 by marcsilv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"
#include <stdio.h>

long long	ft_gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec * 1000));
}

void	shooting(t_cub *cub)
{
	int	i;

	i = SHOOTING_01;
	
	while (i <= SHELL_05)
	{
		my_mlx_put_img_to_img(&cub->img, cub->player.imgs[i],
			(t_point){cub->img.width / 2, (cub->img.height
				- cub->player.imgs[i].height)}, 1);
		usleep(10000);
		i++;
	}
	cub->player.shooting = false;
	cub->player.idle = true;
}


long get_current_time()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void player(t_cub *cub)
{
    my_mlx_draw_ret_to_img(&cub->img, (t_point){10, cub->img.height - 40},
                           (t_point){300, 30}, DARK_GRAY);
    my_mlx_draw_ret_to_img(&cub->img, (t_point){10, cub->img.height - 40},
                           (t_point){((300 * cub->player.health.value) / 100), 30}, RED);
    my_mlx_put_img_to_img(&cub->img, cub->player.imgs[CROSSHAIR],
                          (t_point){(cub->img.width - cub->player.imgs[CROSSHAIR].width) / 2,
                                   (cub->img.height - cub->player.imgs[CROSSHAIR].height) / 2}, 1);
    if (cub->player.idle)
        my_mlx_put_img_to_img(&cub->img, cub->player.imgs[IDLE],
                              (t_point){cub->img.width / 2, (cub->img.height - cub->player.imgs[IDLE].height)}, 1);
}
