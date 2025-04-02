/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:04:00 by efinda            #+#    #+#             */
/*   Updated: 2025/03/31 14:07:53 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static void	init_scene_dfl(t_scene *scene, int i)
{
	scene->fd = 0;
	scene->floor = 0;
	scene->ceiling = 0;
	scene->line_nbr = 0;
	scene->mtx = NULL;
	scene->tmp = NULL;
	scene->line = NULL;
	scene->elements = NULL;
	scene->line_nbr_str = NULL;
	scene->map.head = NULL;
	scene->map.content = NULL;
	scene->map.start = '\0';
	scene->map.spos = (t_point){.x = 0, .y = 0};
	scene->map.size = (t_point){.x = 0, .y = 0};
	while (++i < 4)
	{
		scene->textures[i].id = 0;
		scene->textures[i].path = NULL;
		my_mlx_init_img(&scene->textures[i].img);
	}
}

static void	init_player_dfl(t_player *player)
{
	player->pos = (t_dpoint){0.0, 0.0};
	player->dir = (t_dpoint){0.0, 0.0};
	player->plane = (t_dpoint){0.0, 0.0};
	player->angle = 0.0;
	player->updown = 0;
}

static void	init_minimap_dfl(t_mmap *minimap)
{
	minimap->box = 0;
	my_mlx_init_img(&minimap->img);
	minimap->bounds = (t_point){.x = 0, .y = 0};
	minimap->tilesize = 0;
	minimap->cur = NULL;
	minimap->corners[TOPLEFT] = NULL;
	minimap->corners[TOPRIGHT] = NULL;
	minimap->corners[BOTTLEFT] = NULL;
	minimap->corners[BOTTRIGHT] = NULL;
	minimap->tiles = NULL;
}

static void	init_sprites_dfl(t_sprite *sprites, int i)
{
	sprites->ammo = 8;
	sprites->health = (t_nbr){.value = 100, .str = NULL};
	sprites->idle = true;
	sprites->shooting = false;
	sprites->recharging = false;
	sprites->cur_frame_index = IDLE;
	sprites->last_frame_time = 0;
	while (++i < 27)
		my_mlx_init_img(&sprites->imgs[i]);
}

void	init_dfl(t_cub *cub)
{
	cub->mlx = NULL;
	cub->win = NULL;
	my_mlx_init_img(&cub->img);
	cub->rays = NULL;
	init_scene_dfl(&cub->scene, -1);
	init_player_dfl(&cub->player);
	init_minimap_dfl(&cub->minimap);
	init_sprites_dfl(&cub->sprites, -1);
	cub->hooks.alt = 0;
	cub->hooks.space = 0;
	cub->ppd = 0.0;
}
