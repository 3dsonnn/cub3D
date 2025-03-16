/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:58:45 by efinda            #+#    #+#             */
/*   Updated: 2025/03/16 18:44:58 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D_bonus.h"

void	menu(t_cub *cub, int i)
{
	t_img	tmp;

	tmp.img = mlx_xpm_file_to_image(cub->mlx, "menu.xpm", &tmp.height, &tmp.width);
	if (!tmp.img)
		exit(ft_dprintf(2, "ERRORRRRRRRRRR\n"));
	tmp.addr = (int *)mlx_get_data_addr(tmp.img, &tmp.bpp, &tmp.line_len, &tmp.endian);
	if (!tmp.addr)
		exit(ft_dprintf(2, "ERRORRRRRRRRRR 22222222222\n"));
	tmp.line_len /= 4;
	mlx_set_font(cub->mlx, cub->win, FONT);
	mlx_string_put(cub->mlx, cub->win, tmp.height + 1, tmp.width + 1, 0x00FFFF, "ARE you readyã");
	// mlx_put_image_to_window(cub->mlx, cub->win, tmp.img, 0, 0);
	while (1)
		continue;
	// while (i++ < cub->img.height)
	// {
	// 	pixel.y = (cub->rays[j].texture->img.height * (i
	// 				- cub->rays[j].col.top)) / cub->rays[j].col.height;
	// 	my_mlx_pixel_put(&cub->img, j, i,
	// 		my_mlx_get_pixel(&cub->rays[j].texture->img, pixel.x, pixel.y));
	// 	i++;
	// }
}

int	main(int ac, char **av)
{
	t_cub	cub;

	checks(&cub, ac, av);
	init_mlx(&cub, -1);
	init_minimap(&cub, -1, -1);
	init_rays(&cub);
	init_player(&cub);
	// menu(&cub, -1);
	cub3D(&cub);
	my_mlx_hook(&cub);
	mlx_loop(cub.mlx);
	return (0);
}
