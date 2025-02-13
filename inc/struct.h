/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:50:36 by efinda            #+#    #+#             */
/*   Updated: 2025/02/13 14:50:45 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef enum ID
{
	NO,
	SO,
	WE,
	EA
}					t_ID;

typedef enum CORNERS
{
	TOPLEFT,
	TOPRIGHT,
	BOTTLEFT,
	BOTTRIGHT
}					t_CORNERS;

typedef struct s_iter
{
	int				i;
	int				j;
	int				k;
	int				l;
	int				m;
	int				n;
}					t_iter;

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
	int				*addr;
	int				line_len;
	int				bpp;
	int				endian;
	int				width;
	int				height;
}					t_img;

typedef struct s_fc
{
	int				color;
	int				rgb[3];
}					t_fc;

typedef struct s_texture
{
	t_ID			id;
	char			*path;
	t_img			img;
}					t_texture;

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
	t_texture		textures[4];
}					t_scene;

typedef struct s_tile
{
	char			*id;
	int				color;
	t_point			crd;
	struct s_tile	*up;
	struct s_tile	*down;
	struct s_tile	*left;
	struct s_tile	*right;
	struct s_tile	*upleft;
	struct s_tile	*upright;
	struct s_tile	*downleft;
	struct s_tile	*downright;
}					t_tile;

typedef struct s_col
{
	double		dist;
	int			height;
	int			top;
	int			bottom;
	int			dist_from_top;
	t_texture	*texture;
}				t_col;

typedef struct s_intersection
{
	double		dist;
	t_dpoint	step;
	t_dpoint	crd;
	t_dpoint	wall;
	int			intersected;
}				t_intersection;

typedef struct s_ray
{
	double			angle;
	double			dist;
	double			tan;
	t_point			dir;
	t_dpoint		wall;
	t_intersection	hor;
	t_intersection	ver;
	t_col			col;
}					t_ray;

typedef struct s_player
{
	t_dplane		pos;
	t_dpoint		fov;
	t_dplane		dir;
	double			angle;
	int				size;
	t_tile			*neighbors[8];
}					t_player;

typedef struct s_mmap
{
	int				box;
	int				tilesize;
	t_tile			*cur;
	t_tile			*corners[4];
	t_tile			**tiles;
}					t_mmap;

typedef struct s_cub
{
	void			*mlx;
	void			*win;
	t_img			img;
	t_scene			scene;
	t_mmap			minimap;
	t_player		player;
	t_ray			*rays;
	double			ppd;
}					t_cub;

#endif