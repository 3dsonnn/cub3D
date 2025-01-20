/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 01:16:17 by efinda            #+#    #+#             */
/*   Updated: 2025/01/20 01:18:37 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static void	get_ifpos_aux(t_cub *cub)
{
	cub->player.ifpos[IFUPLEFT] = (t_plane){cub->player.pos.x0
		- cub->player.size.x, cub->player.pos.x - cub->player.size.x,
		cub->player.pos.y0 - cub->player.size.y, cub->player.pos.y
		- cub->player.size.y};
	cub->player.ifpos[IFUPRIGHT] = (t_plane){cub->player.pos.x0
		+ cub->player.size.x, cub->player.pos.x + cub->player.size.x,
		cub->player.pos.y0 - cub->player.size.y, cub->player.pos.y
		- cub->player.size.y};
	cub->player.ifpos[IFDOWNLEFT] = (t_plane){cub->player.pos.x0
		- cub->player.size.x, cub->player.pos.x - cub->player.size.x,
		cub->player.pos.y0 + cub->player.size.y, cub->player.pos.y
		+ cub->player.size.y};
	cub->player.ifpos[IFDOWNRIGHT] = (t_plane){cub->player.pos.x0
		+ cub->player.size.x, cub->player.pos.x + cub->player.size.x,
		cub->player.pos.y0 + cub->player.size.y, cub->player.pos.y
		+ cub->player.size.y};
}

void	get_ifpos(t_cub *cub)
{
	cub->player.ifpos[IFUP] = (t_plane){cub->player.pos.x0, cub->player.pos.x,
		cub->player.pos.y0 - cub->player.size.y, cub->player.pos.y
		- cub->player.size.y};
	cub->player.ifpos[IFDOWN] = (t_plane){cub->player.pos.x0, cub->player.pos.x,
		cub->player.pos.y0 + cub->player.size.y, cub->player.pos.y
		+ cub->player.size.y};
	cub->player.ifpos[IFLEFT] = (t_plane){cub->player.pos.x0
		- cub->player.size.x, cub->player.pos.x - cub->player.size.x,
		cub->player.pos.y0, cub->player.pos.y};
	cub->player.ifpos[IFRIGHT] = (t_plane){cub->player.pos.x0
		+ cub->player.size.x, cub->player.pos.x + cub->player.size.x,
		cub->player.pos.y0, cub->player.pos.y};
	get_ifpos_aux(cub);
}

void	init_player(t_cub *cub, int i, int j)
{
	cub->player.size.x = (int)floor(cub->minimap.tilewidth / 6);
	cub->player.size.y = (int)floor(cub->minimap.tileheight / 6);
	while (++i < cub->scene.map.size.y)
	{
		j = -1;
		while (++j < cub->scene.map.size.x)
		{
			if (cub->minimap.tiles[i][j].id == 'E')
			{
				cub->player.pos.x0 = cub->minimap.tiles[i][j].pos.x0;
				cub->player.pos.y0 = cub->minimap.tiles[i][j].pos.y0;
				cub->player.pos.x = cub->player.pos.x0 + cub->player.size.x;
				cub->player.pos.y = cub->player.pos.y0 + cub->player.size.y;
				cub->player.tile = &cub->minimap.tiles[i][j];
			}
		}
	}
	get_ifpos(cub);
}