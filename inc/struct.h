/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welepy <welepy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:50:36 by efinda            #+#    #+#             */
/*   Updated: 2025/01/12 10:15:28 by welepy           ###   ########.fr       */
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
}			t_ID;

typedef struct s_wall
{
	t_ID	id;
	int		fd;
}			t_wall;

typedef struct s_fc
{
	t_ID	id;
	int		rgb[3];
}			t_fc;

typedef struct s_map
{
	char	**content;
	char	start;
	t_point	size;
	t_point	init;
	t_point	neighbor;
	t_point	cur;
	int	dx[4];
	int	dy[4];
	int	nx;
	int	ny;
	bool	**visited;
}			t_map;

typedef struct s_scene
{
	int		fd;
	char	*tmp;
	char	*line;
	char	**mtx;
	char	*elements;
	t_map	map;
	t_fc	fc[2];
	t_wall	walls[4];
}			t_scene;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_cub
{
	t_img	*img;
	t_scene	scene;
}			t_cub;

#endif