/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:50:36 by efinda            #+#    #+#             */
/*   Updated: 2025/01/17 12:28:21 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef enum ID
{
	NO,
	SO,
	WE,
	EA,
	F,
	C
}					t_ID;

typedef struct s_rows
{
	char			*str;
	struct s_rows	*next;
}					t_rows;

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
}					t_img;

typedef struct s_fc
{
	t_ID			id;
	int				rgb[3];
}					t_fc;

typedef struct s_wall
{
	t_ID			id;
	char			*path;
	int				width;
	int				height;
	t_img			img;
}					t_wall;

typedef struct s_map
{
	t_rows			*head;
	char			**content;
	char			start;
	t_point			spos;
	t_point			size;
}					t_map;

typedef struct s_scene
{
	int				fd;
	char			*tmp;
	char			*line;
	char			*elements;
	t_map			map;
	t_fc			fc[2];
	t_wall			walls[4];
}					t_scene;

typedef struct s_plane
{
	int				x0;
	int				x;
	int				y0;
	int				y;
}					t_plane;

typedef struct s_tile
{
	char			id;
	int				color;
	t_plane			pos;
	struct s_tile	*prev;
	struct s_tile	*next;
	struct s_tile	*up;
	struct s_tile	*down;
}					t_tile;

typedef struct s_player
{
	int				i;
	int				j;
	t_point			size;
	t_plane			pos;
	t_plane			to_wall;
	t_point			fov;
	t_point			dir;
	struct s_tile	*prev;
	struct s_tile	*next;
	struct s_tile	*up;
	struct s_tile	*down;
}					t_player;

typedef struct s_mmap
{
	int				width;
	int				height;
	int				remainder_width;
	int				remainder_height;
	int				extra_width;
	int				extra_height;
	t_tile			**tiles;
	t_img			img;
}					t_mmap;

typedef struct s_cub
{
	void			*mlx;
	void			*win;
	t_img			img;
	t_point			size;
	t_mmap			minimap;
	t_player		player;
	t_scene			scene;
}					t_cub;

#endif