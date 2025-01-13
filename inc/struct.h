/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:50:36 by efinda            #+#    #+#             */
/*   Updated: 2025/01/13 15:17:07 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stdbool.h>

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

typedef struct s_fc
{
	t_ID			id;
	int				rgb[3];
}					t_fc;

typedef struct s_wall
{
	t_ID			id;
	char			*path;
	void			*img;
	int				width;
	int				height;
}					t_wall;

typedef struct s_map
{
	t_rows			*head;
	char			**content;
	char			start;
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

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
}					t_img;

typedef struct s_cub
{
	void			*mlx;
	void			*win;
	t_img			img[4];
	t_scene			scene;
}					t_cub;

#endif