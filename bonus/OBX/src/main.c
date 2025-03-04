/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:58:45 by efinda            #+#    #+#             */
/*   Updated: 2025/02/05 23:28:11 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/obx.h"

int	main(int ac, char **av)
{
	t_obx	obx;

	checks(&obx.map, ac, av);
	my_mlx_init(&obx, -1, -1);
	my_mlx_hook(&obx);
	bounding_box(&obx, -1, -1);
	mlx_loop(obx.mlx);
	return (0);
}
