/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:50:36 by efinda            #+#    #+#             */
/*   Updated: 2025/01/23 10:30:22 by efinda           ###   ########.fr       */
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

typedef enum IFPOS
{
	IFUP,
	IFDOWN,
	IFLEFT,
	IFRIGHT,
	IFUPLEFT,
	IFUPRIGHT,
	IFDOWNLEFT,
	IFDOWNRIGHT
}					t_IFPOS;

typedef struct s_dpoint
{
	double			x;
	double			y;
}					t_dpoint;

typedef struct s_dplane
{
	double			x0;
	double			x;
	double			y0;
	double			y;
}					t_dplane;

typedef struct s_plane
{
	int				x0;
	int				x;
	int				y0;
	int				y;
}					t_plane;

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

typedef struct s_tile
{
	char			id;
	int				color;
	t_plane			pos;
	struct s_tile	*up;
	struct s_tile	*down;
	struct s_tile	*left;
	struct s_tile	*right;
	struct s_tile	*upleft;
	struct s_tile	*upright;
	struct s_tile	*downleft;
	struct s_tile	*downright;
}					t_tile;

typedef struct s_ray
{
	t_point			face;
	t_dpoint		hor;
	t_dpoint		vert;
	t_dpoint		step;
	double			angle;
	double			tan;
}					t_ray;

typedef struct s_player
{
	t_point			size;
	t_plane			pos;
	t_dpoint		fov;
	t_dplane		dir;
	double			ray_step;
	double			angle;
	struct s_tile	*tile;
}					t_player;

typedef struct s_mmap
{
	int				miniwidth;
	int				miniheight;
	int				tilewidth;
	int				tileheight;
	t_tile			**tiles;
	t_img			img;
}					t_mmap;

typedef struct s_cub
{
	int				flag;
	void			*mlx;
	void			*win;
	t_img			img;
	t_mmap			minimap;
	t_player		player;
	t_scene			scene;
}					t_cub;

#endif