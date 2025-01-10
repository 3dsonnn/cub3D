/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:50:36 by efinda            #+#    #+#             */
/*   Updated: 2025/01/10 01:06:57 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_wall
{
    int     fd;
	char    *ID;
    char    *path;
}		t_wall;

typedef struct s_fc
{
    int     fd;
	char    *ID;
    char    *range;
    int     r;
    int     g;
    int     b;
}		t_fc;

typedef struct s_map
{
    char    **map;
    t_fc    fc[2];
    t_wall  walls[4];
}   t_map;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}		t_img;

typedef struct s_cub
{
	int     fd;
    char    *line;
    char    *tmp;
    char    **mtx;
    t_img   img;
    t_map   map;
}		t_cub;

#endif