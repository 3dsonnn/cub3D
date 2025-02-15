/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:58:45 by efinda            #+#    #+#             */
/*   Updated: 2025/02/13 15:46:51 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int	main(int ac, char **av)
{
	t_cub	cub;

	checks(&cub, ac, av);
	init_mlx(&cub, -1);
	init_rays(&cub);
	init_player(&cub);
	cub3D(&cub, -1);
	my_mlx_hook(&cub);
	mlx_loop(cub.mlx);
	return (0);
}
