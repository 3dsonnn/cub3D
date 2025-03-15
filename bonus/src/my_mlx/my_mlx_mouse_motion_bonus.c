/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_mouse_motion_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 02:34:28 by efinda            #+#    #+#             */
/*   Updated: 2025/03/15 03:30:53 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static  void	*my_mlx_mouse_motion_hook(void *arg)
{
	t_mouse_motion	*mouse;
	
	mouse = (t_mouse_motion *)arg;
	while (!0)
	{
        if (mouse->exit)
            break ;
		mlx_mouse_get_pos(mouse->cub->mlx, mouse->cub->win, &mouse->crd.x, &mouse->crd.y);
        if (mouse->crd.x != (int)(mouse->cub->img.width / 2))
        {
            ft_printf("Mouse moved: x=%d\n", mouse->crd.x);
            if (mouse->crd.x < (int)(mouse->cub->img.width / 2))
                my_mlx_key_press(LEFT, mouse->cub);
            else
                my_mlx_key_press(RIGHT, mouse->cub);
        }
		else
			continue ;
		mlx_mouse_move(mouse->cub->mlx, mouse->cub->win, (int)(mouse->cub->img.width / 2), (int)(mouse->cub->img.height / 2));
	}
}

void    my_mlx_mouse_motion(t_mouse_motion *mouse)
{
    int	i;

	i = -1;
    mouse->exit = 0;
    if (pthread_create(&mouse->thread, NULL, my_mlx_mouse_motion_hook, mouse))
    {
		ft_dprintf(2, "Error\nFailed to create mouse motion thread");
        free_tiles(&mouse->cub->minimap.tiles, -1, mouse->cub->scene.map.size.y);
        while (++i < 4)
            mlx_destroy_image(mouse->cub->mlx, mouse->cub->scene.textures[i].img.img);
        mlx_destroy_image(mouse->cub->mlx, mouse->cub->img.img);
        mlx_destroy_window(mouse->cub->mlx, mouse->cub->win);
        mlx_destroy_display(mouse->cub->mlx);
        free(mouse->cub->rays);
        free(mouse->cub->mlx);
        exit(1);
    }
}
