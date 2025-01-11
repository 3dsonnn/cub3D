/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:50:36 by efinda            #+#    #+#             */
/*   Updated: 2025/01/11 15:48:56 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef	enum	ID
{
	NO,
	SO,
	WE,
	EA,
	F,
	C
}	t_ID;

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
	int		rows;
	int		cols;
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