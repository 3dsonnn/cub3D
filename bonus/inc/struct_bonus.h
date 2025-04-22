/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcsilv <marcsilv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:50:36 by efinda            #+#    #+#             */
/*   Updated: 2025/04/16 21:01:44 by marcsilv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_BONUS_H
# define STRUCT_BONUS_H

# define CROSSHAIR_PATH "bonus/config/animated_sprites/crosshair.xpm"
# define IDLE_PATH "bonus/config/animated_sprites/shotgun/idle.xpm"
# define PUTTING_01_PATH "bonus/config/animated_sprites/shotgun/putting01.xpm"
# define PUTTING_02_PATH "bonus/config/animated_sprites/shotgun/putting02.xpm"
# define PUTTING_03_PATH "bonus/config/animated_sprites/shotgun/putting03.xpm"
# define RECHARGING_01_PATH "bonus/config/animated_sprites/shotgun/recharging01.xpm"
# define RECHARGING_02_PATH "bonus/config/animated_sprites/shotgun/recharging02.xpm"
# define RECHARGING_03_PATH "bonus/config/animated_sprites/shotgun/recharging03.xpm"
# define RECHARGING_04_PATH "bonus/config/animated_sprites/shotgun/recharging04.xpm"
# define RECHARGING_05_PATH "bonus/config/animated_sprites/shotgun/recharging05.xpm"
# define RECHARGING_06_PATH "bonus/config/animated_sprites/shotgun/recharging06.xpm"
# define RECHARGING_IDLE_PATH "bonus/config/animated_sprites/shotgun/recharging_idle.xpm"
# define SHELL_01_PATH "bonus/config/animated_sprites/shotgun/shell01.xpm"
# define SHELL_02_PATH "bonus/config/animated_sprites/shotgun/shell02.xpm"
# define SHELL_03_PATH "bonus/config/animated_sprites/shotgun/shell03.xpm"
# define SHELL_04_PATH "bonus/config/animated_sprites/shotgun/shell04.xpm"
# define SHELL_05_PATH "bonus/config/animated_sprites/shotgun/shell05.xpm"
# define SHELL_06_PATH "bonus/config/animated_sprites/shotgun/shell06.xpm"
# define SHELL_07_PATH "bonus/config/animated_sprites/shotgun/shell07.xpm"
# define SHELL_08_PATH "bonus/config/animated_sprites/shotgun/shell08.xpm"
# define SHELL_09_PATH "bonus/config/animated_sprites/shotgun/shell09.xpm"
# define SHOOTING_01_PATH "bonus/config/animated_sprites/shotgun/shooting01.xpm"
# define SHOOTING_02_PATH "bonus/config/animated_sprites/shotgun/shooting02.xpm"
# define SHOOTING_IDLE_PATH "bonus/config/animated_sprites/shotgun/shooting_idle.xpm"
# define CARTIDGE_PATH "bonus/config/cartidge.xpm"
# define DOOR "./images/door.xpm"
# define MAX_AMMO 8

typedef enum e_ID
{
	NO,
	SO,
	WE,
	EA
}					t_ID;

typedef struct s_img_path
{
	int				key;
	char			*path;
}					t_img_path;

typedef enum e_player_img
{
	CROSSHAIR,
	IDLE,
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
	SHOOTING_01,
	SHOOTING_02,
	SHELL_01,
	SHELL_02,
	SHELL_03,
	SHELL_04,
	SHELL_05,
	SHELL_06,
	SHELL_07,
	SHELL_08,
	SHELL_09,
	CARTIDGE,
	TMP
}					t_player_img;

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

typedef struct s_nbr
{
	int				value;
	char			*str;
}					t_nbr;

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
	t_plane			axis;
	int				radius;
	int				decision;
	int				color;
	t_img			*img;
}					t_bresenham_circle;

typedef struct s_hook
{
	int				alt;
	int				space;
}					t_hook;

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
	t_texture		door;
}					t_scene;

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
	bool			is_door;
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
	t_nbr			health;
	bool			idle;
	bool			shooting;
	bool			recharging;
	t_img			imgs[25];
	int				ammo;
	int current_frame;
	long last_frame_time;
}					t_player;

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
	t_hook			hooks;
	double			ppd;
}					t_cub;

#endif

