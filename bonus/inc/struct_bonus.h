/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:50:36 by efinda            #+#    #+#             */
/*   Updated: 2025/05/06 15:39:15 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_BONUS_H
# define STRUCT_BONUS_H

# include <stdbool.h>

typedef struct s_img	t_img;
typedef struct s_cub	t_cub;

typedef enum e_frames
{
	CROSSHAIR,
	IDLE,
	SHOOTING_01,
	SHOOTING_02,
	SHOOTING_IDLE,
	SHELL_01,
	SHELL_02,
	SHELL_03,
	SHELL_04,
	SHELL_05,
	SHELL_06,
	SHELL_07,
	SHELL_08,
	SHELL_09,
	PUTTING_01,
	PUTTING_02,
	PUTTING_03,
	RECHARGING_01,
	RECHARGING_02,
	RECHARGING_03,
	RECHARGING_04,
	RECHARGING_05,
	RECHARGING_06,
	RECHARGING_IDLE,
	CLEAR,
}						t_frames;

typedef enum e_ID
{
	NO,
	SO,
	WE,
	EA
}						t_ID;

typedef enum e_CORNERS
{
	TOPLEFT,
	TOPRIGHT,
	BOTTLEFT,
	BOTTRIGHT
}						t_CORNERS;

typedef struct s_dpoint
{
	double				x;
	double				y;
}						t_dpoint;

typedef struct s_dplane
{
	double				x0;
	double				x;
	double				y0;
	double				y;
}						t_dplane;

typedef struct s_plane
{
	int					x0;
	int					x;
	int					y0;
	int					y;
}						t_plane;

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

typedef struct s_bresenham_line
{
	t_plane				crd;
	t_point				dist;
	t_point				dir;
	int					error;
	int					updated_error;
	int					color;
	t_img				*img;
}						t_bresenham_line;

typedef struct s_bresenham_circle
{
	t_point				center;
	t_point				limits;
	t_plane				axis;
	int					radius;
	int					decision;
	int					color;
	t_img				*img;
}						t_bresenham_circle;

typedef struct s_img_path
{
	int					key;
	char				*path;
}						t_img_path;

struct					s_img
{
	void				*img;
	int					*addr;
	int					line_len;
	int					bpp;
	int					endian;
	int					width;
	int					height;
};

typedef struct s_map_crd
{
	char				*str;
	struct s_map_crd	*next;
}						t_map_crd;

typedef struct s_row
{
	char				*str;
	char				*line_nbr;
	struct s_row		*prev;
	struct s_row		*next;
}						t_row;

typedef struct s_door
{
	int					i;
	t_point				dir;
	int					points[4];
	t_img				door;
	t_img				key;
}						t_door;

typedef struct s_map
{
	t_row				*head;
	t_map_crd			*crds;
	char				**content;
	char				start;
	t_point				spos;
	t_point				size;
	t_door				door;
}						t_map;

typedef struct s_nbr
{
	int					value;
	char				*str;
}						t_nbr;

typedef struct s_texture
{
	t_ID				id;
	char				*path;
	t_img				img;
}						t_texture;

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
	int					is_door;
	int					intersected;
}						t_intersection;

typedef struct s_ray
{
	double				angle;
	double				dist;
	double				tan;
	int					height;
	int					top;
	int					bot;
	t_point				dir;
	t_dpoint			wall;
	t_intersection		hor;
	t_intersection		ver;
	t_img				img;
}						t_ray;

typedef struct s_hook
{
	int alt : 1;
	int space : 1;
}						t_hook;

typedef struct s_sprite
{
	int					i;
	bool				idle;
	bool				shooting;
	bool				recharging;
	int					cur_frame_index;
	int					cur_frame;
	unsigned long long	last_frame_time;
	t_img				imgs[25];
}						t_sprite;

typedef struct s_tile
{
	char				id;
	int					color;
	t_point				crd;
	struct s_tile		*up;
	struct s_tile		*down;
	struct s_tile		*left;
	struct s_tile		*right;
}						t_tile;

typedef struct s_mmap
{
	t_img				img;
	t_img				circle;
	t_img				rotated;
	t_img				padded;
	double				angle;
	t_tile				*cur;
	t_tile				*corners[4];
	t_tile				**tiles;
}						t_mmap;

typedef struct s_player
{
	t_dpoint			pos;
	t_dpoint			dir;
	t_dpoint			plane;
	double				angle;
	int					updown;
}						t_player;

struct					s_cub
{
	void				*mlx;
	void				*win;
	t_ray				*rays;
	t_img				img;
	t_scene				scene;
	t_player			player;
	t_mmap				minimap;
	t_hook				hooks;
	t_sprite			sprites;
	double				ppd;
};

#endif
