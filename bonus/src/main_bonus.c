/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:58:45 by efinda            #+#    #+#             */
/*   Updated: 2025/03/15 04:20:24 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D_bonus.h"

int	main(int ac, char **av)
{
	t_cub	cub;

	checks(&cub, ac, av);
	init_mlx(&cub, -1);
	init_minimap(&cub, -1, -1);
	init_rays(&cub);
	init_player(&cub);
	cub3D(&cub);
	my_mlx_hook(&cub);
	// my_mlx_mouse_motion(&cub.mouse);
	mlx_loop(cub.mlx);
	return (0);
}
