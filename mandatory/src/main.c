/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:58:45 by efinda            #+#    #+#             */
/*   Updated: 2025/04/30 17:42:08 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int	main(int ac, char **av)
{
	t_cub	cub;

	init_dfl(&cub, -1);
	checks(&cub, ac, av);
	init_mlx(&cub);
	init_rays(&cub);
	init_player(&cub);
	raycast(&cub, -1);
	my_mlx_hook(&cub);
	mlx_loop(cub.mlx);
	return (0);
}
