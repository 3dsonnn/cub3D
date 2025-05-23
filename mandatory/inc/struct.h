/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:50:36 by efinda            #+#    #+#             */
/*   Updated: 2025/05/06 14:00:57 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_cub	t_cub;

typedef enum ID
{
	NO,
	SO,
	WE,
	EA
}						t_ID;

typedef struct s_iter
{
	int					i;
	int					j;
	int					k;
	int					l;
	int					m;
	int					n;
}						t_iter;

typedef struct s_strs
{
	char				*s1;
	char				*s2;
	char				*s3;
	char				*s4;
	char				*s5;
	char				*s6;
}						t_strs;

typedef struct s_plane
{
	int					x0;
	int					x;
	int					y0;
	int					y;
}						t_plane;

typedef struct s_dpoint
{
	double				x;
	double				y;
}						t_dpoint;

typedef struct s_rows
{
	char				*str;
	struct s_rows		*next;
}						t_rows;

typedef struct s_nbr
{
	int					value;
	char				*str;
}						t_nbr;

typedef struct s_row
{
	char				*str;
	char				*line_nbr;
	struct s_row		*prev;
	struct s_row		*next;
}						t_row;

typedef struct s_map_crd
{
	char				*str;
	struct s_map_crd	*next;
}						t_map_crd;

typedef struct s_img
{
	void				*img;
	int					*addr;
	int					line_len;
	int					bpp;
	int					endian;
	int					width;
	int					height;
}						t_img;

typedef struct s_texture
{
	char				*path;
	t_img				img;
}						t_texture;

typedef struct s_map
{
	t_row				*head;
	t_map_crd			*crds;
	char				**content;
	char				start;
	t_point				spos;
	t_point				size;
}						t_map;

typedef struct s_scene
{
	int					fd;
	int					floor;
	int					ceiling;
	char				**mtx;
	char				*tmp;
	char				*line;
	char				*line_cpy;
	char				*elements;
	t_nbr				line_nbr;
	t_map				map;
	t_texture			textures[4];
	t_cub				*cub;
}						t_scene;

typedef struct s_intersection
{
	double				dist;
	t_dpoint			step;
	t_dpoint			crd;
	t_dpoint			wall;
	int					intersected;
}						t_intersection;

typedef struct s_ray
{
	double				angle;
	double				dist;
	double				tan;
	int					top;
	int					bot;
	int					height;
	t_point				dir;
	t_dpoint			wall;
	t_intersection		hor;
	t_intersection		ver;
	t_img				img;
}						t_ray;

typedef struct s_player
{
	t_dpoint			pos;
	t_dpoint			dir;
	t_dpoint			plane;
	double				angle;
}						t_player;

struct					s_cub
{
	void				*mlx;
	void				*win;
	t_img				img;
	t_scene				scene;
	t_player			player;
	t_ray				*rays;
	double				ppd;
};

#endif
