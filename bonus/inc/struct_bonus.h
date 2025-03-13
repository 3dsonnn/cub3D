/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:50:36 by efinda            #+#    #+#             */
/*   Updated: 2025/03/13 09:27:05 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_BONUS_H
# define STRUCT_BONUS_H

typedef enum e_ID
{
	NO,
	SO,
	WE,
	EA
}					t_ID;

typedef enum e_CORNERS
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

typedef struct s_strs
{
	char			*s1;
	char			*s2;
	char			*s3;
	char			*s4;
	char			*s5;
	char			*s6;
}					t_strs;

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

typedef struct s_bresenham_line
{
	t_plane			crd;
	t_point			dist;
	t_point			dir;
	int				error;
	int				updated_error;
	int				color;
	t_img			*img;
}					t_bresenham_line;

typedef struct s_bresenham_circle
{
	t_point			center;
	t_point			crd;
	int				radius;
	int				decision;
	int				color;
	t_img			*img;
}					t_bresenham_circle;

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
	int				floor;
	int				ceiling;
	int				line_nbr;
	char			**mtx;
	char			*tmp;
	char			*line;
	char			*elements;
	char			*line_nbr_str;
	t_map			map;
	t_texture		textures[4];
}					t_scene;

typedef struct s_col
{
	double			dist;
	int				height;
	int				top;
	int				bot;
}					t_col;

typedef struct s_intersection
{
	double			dist;
	t_dpoint		step;
	t_dpoint		crd;
	t_dpoint		wall;
	int				intersected;
}					t_intersection;

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
	t_texture		*texture;
}					t_ray;

typedef struct s_player
{
	t_dpoint		pos;
	t_dplane		dir;
	t_dpoint		plane;
	double			angle;
}					t_player;

typedef struct s_tile
{
	char			id;
	int				color;
	t_point			crd;
	struct s_tile	*up;
	struct s_tile	*down;
	struct s_tile	*left;
	struct s_tile	*right;
}					t_tile;

typedef struct s_mmap
{
	int				box;
	t_point			bounds;
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
	t_player		player;
	t_ray			*rays;
	t_mmap			minimap;
	double			ppd;
}					t_cub;

#endif
