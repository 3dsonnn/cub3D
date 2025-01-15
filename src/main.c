/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:58:45 by efinda            #+#    #+#             */
/*   Updated: 2025/01/15 11:18:53 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

//  TMP FUNCTIONS
void	print_map(t_map *map)
{
	int	i;

	i = -1;
	while (++i < map->size.y)
		printf("%s\n", map->content[i]);
	printf("\n");
}

int main(int ac, char **av)
{
    t_cub   cub;

    checks(&cub.scene, ac, av);
    my_mlx_init(&cub);
    my_mlx_hook(&cub);
	cub3D(&cub);
	mlx_loop(cub.mlx);
    return (0);
}
