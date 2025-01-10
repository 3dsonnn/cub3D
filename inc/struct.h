/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:50:36 by efinda            #+#    #+#             */
/*   Updated: 2025/01/10 04:08:41 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef	enum	ID
{
	C = 0,
	F = 1,
	EA = 0,
	NO = 1,
	SO = 2,
	WE = 3
}	t_ID;

typedef struct s_wall
{
	int		fd;
	t_ID	id;
	char	*path;
}			t_wall;

typedef struct s_fc
{
	t_ID	id;
	int		rgb[3];
}			t_fc;

typedef struct s_elem
{
	t_ID	id;
	int		rgb[3];
}			t_elem;

typedef struct s_scene
{
	int		fd;
	char	*tmp;
	char	*line;
	char	**mtx;
	char	**map;
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