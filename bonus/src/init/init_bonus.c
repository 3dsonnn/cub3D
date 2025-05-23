/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 12:04:00 by efinda            #+#    #+#             */
/*   Updated: 2025/05/06 16:58:29 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

static void	init_scene_dfl(t_scene *scene, t_cub *cub, int i)
{
	scene->fd = 0;
	scene->floor = 0;
	scene->ceiling = 0;
	scene->cub = cub;
	scene->mtx = NULL;
	scene->tmp = NULL;
	scene->line = NULL;
	scene->line_cpy = NULL;
	scene->elements = NULL;
	scene->line_nbr = (t_nbr){.value = 0, .str = NULL};
	scene->map = (t_map){.head = NULL, .crds = NULL, .content = NULL,
		.start = '\0', .spos = (t_point){.x = 0, .y = 0}, .door.i = 0,
		.door.dir = (t_point){.x = 0, .y = 0}, .door.points = {0, 0, 0, 0},
		.size = (t_point){.x = 0, .y = 0}};
	my_mlx_init_img(&scene->map.door.key);
	my_mlx_init_img(&scene->map.door.door);
	while (++i < 4)
	{
		scene->textures[i].id = 0;
		scene->textures[i].path = NULL;
		my_mlx_init_img(&scene->textures[i].img);
	}
}

static void	init_player_minimap_sprites_dfl(t_player *player, t_mmap *minimap,
		t_sprite *sprites, int i)
{
	*player = (t_player){.pos = (t_dpoint){0.0, 0.0}, .dir = (t_dpoint){0.0,
		0.0}, .angle = 0.0, .plane = (t_dpoint){0.0, 0.0}, .updown = 0};
	*minimap = (t_mmap){.cur = NULL, .angle = (90 * (M_PI / 180)),
		.tiles = NULL, .corners = {NULL, NULL, NULL, NULL}};
	my_mlx_init_img(&minimap->img);
	my_mlx_init_img(&minimap->circle);
	my_mlx_init_img(&minimap->rotated);
	my_mlx_init_img(&minimap->padded);
	*sprites = (t_sprite){.i = 0, .idle = true, .shooting = false,
		.recharging = false, .cur_frame_index = IDLE, .cur_frame = IDLE,
		.last_frame_time = 0};
	while (++i < 25)
		my_mlx_init_img(&sprites->imgs[i]);
}

void	init_dfl(t_cub *cub)
{
	cub->mlx = NULL;
	cub->win = NULL;
	srand(time(NULL));
	my_mlx_init_img(&cub->img);
	cub->rays = NULL;
	init_scene_dfl(&cub->scene, cub, -1);
	init_player_minimap_sprites_dfl(&cub->player, &cub->minimap, &cub->sprites,
		-1);
	cub->hooks = (t_hook){.alt = 0, .space = 0};
	cub->ppd = 0.0;
}

void	init_rays(t_cub *cub)
{
	cub->rays = (t_ray *)ft_calloc(cub->img.width, sizeof(t_ray));
	if (!cub->rays)
		exit_cub(cub, "Failed to allocate memory for rays");
	cub->ppd = (cub->img.width / 2) / tan(FOV / 2);
}
