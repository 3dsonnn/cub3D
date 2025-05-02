/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:58:45 by efinda            #+#    #+#             */
/*   Updated: 2025/05/02 00:00:15 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D_bonus.h"

int	main(int ac, char **av)
{
	t_cub	cub;

	init_dfl(&cub);
	checks(&cub, ac, av);
	init_mlx(&cub);
	init_minimap(&cub);
	init_rays(&cub);
	init_player(&cub);
	cub3d(&cub);
	my_mlx_hook(&cub);
	mlx_loop(cub.mlx);
	return (0);
}
