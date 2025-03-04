/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:58:45 by efinda            #+#    #+#             */
/*   Updated: 2025/03/03 23:43:26 by efinda           ###   ########.fr       */
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
	cub3D(&cub);
	my_mlx_hook(&cub);
	mlx_loop(cub.mlx);
	return (0);
}
