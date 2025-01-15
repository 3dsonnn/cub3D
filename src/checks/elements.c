/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:36:43 by efinda            #+#    #+#             */
/*   Updated: 2025/01/13 20:26:03 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static int	check_id(char *line, int flag)
{
	if (flag)
	{
		if (ft_strncmp(line, "C ", 2) == 0)
			return (1);
		if (ft_strncmp(line, "F ", 2) == 0)
			return (1);
	}
	else
	{
		if (ft_strncmp(line, "NO ", 3) == 0)
			return (1);
		if (ft_strncmp(line, "SO ", 3) == 0)
			return (1);
		if (ft_strncmp(line, "WE ", 3) == 0)
			return (1);
		if (ft_strncmp(line, "EA ", 3) == 0)
			return (1);
	}
	return (0);
}

static void	check_color_range(t_scene *scene, int len, int rgb[3])
{
	char	*aux;

	aux = scene->tmp;
	len = ft_strlen(scene->tmp);
	if (len < 5 || len > 11 || *scene->tmp == ',' || scene->tmp[len - 1] == ',')
		exit_error("Syntax error in the color range of an element", scene);
	rgb[0] = ft_atoi(scene->tmp);
	scene->tmp = ft_strchr(scene->tmp, ',');
	if (*(scene->tmp + 1) == ',')
	{
		scene->tmp = aux;
		exit_error("Syntax error in the color range of an element", scene);
	}
	rgb[1] = ft_atoi(scene->tmp + 1);
	scene->tmp = ft_strchr(scene->tmp, ',');
	rgb[2] = ft_atoi(scene->tmp + 1);
	if (!(rgb[0] >= 0 && rgb[0] <= 255) || !(rgb[1] >= 0 && rgb[1] <= 255)
		|| !(rgb[2] >= 0 && rgb[2] <= 255))
	{
		scene->tmp = aux;
		exit_error("Color out of range in an element", scene);
	}
}

static void	check_fc(t_scene *scene, int i, int j, int len)
{
	int		rgb[3];
	char	*aux;
	char	**mtx;
	char	ID;

	while (scene->line[++i])
		if (!ft_strchr("0123456789 ,", scene->line[i]))
			exit_error("Invalid element in the scene file", scene);
	mtx = ft_split(scene->line, ' ');
	len = ft_mtxlen(mtx);
	if (len < 2 || len > 6 || (strcmp(*mtx, "F") && strcmp(*mtx, "C"))
		|| strcmp(mtx[1], ",") == 0 || strcmp(mtx[len - 1], ",") == 0)
	{
		ft_mtxfree(&mtx);
		exit_error("Invalid element in the scene file", scene);
	}
	while (mtx[++j])
		scene->tmp = ft_strjoin_free(scene->tmp, mtx[j]);
	ID = *mtx[0];
	ft_mtxfree(&mtx);
	aux = scene->tmp;
	check_color_range(scene, 0, rgb);
	fill_fc(scene, ID, rgb, -1);
	ft_strfree(&scene->line);
	ft_strfree(&aux);
}

static void	check_texture(t_scene *scene)
{
	char	**mtx;

	mtx = ft_split(scene->line, ' ');
	if (ft_mtxlen(mtx) != 2)
	{
		ft_mtxfree(&mtx);
		exit_error("Invalid path to a texture element: It cannot contain spaces",
			scene);
	}
	if (open(mtx[1], O_RDONLY) < 0)
	{
		ft_mtxfree(&mtx);
		scene->tmp = ft_strjoin("Invalid path to a texture element: ",
				strerror(errno));
		exit_error(scene->tmp, scene);
	}
	fill_texture(scene, *scene->line, mtx[1]);
	ft_mtxfree(&mtx);
	ft_strfree(&scene->line);
}

void	check_element(t_scene *scene)
{
	scene->tmp = ft_strtrim(scene->line, " ");
	ft_strfree(&scene->line);
	ft_swaptr((void **)&scene->line, (void **)&scene->tmp);
	if (!ft_strchr(scene->line, ' ') || (!check_id(scene->line, 0)
			&& !check_id(scene->line, 1)))
		exit_error("Invalid element in the scene file", scene);
	if (check_id(scene->line, 0))
	{
		if (ft_strlen(scene->line + 3) < 5)
			exit_error("Invalid path to a texture: too short", scene);
		if (ft_strncmp((scene->line + 3) + ft_strlen(scene->line + 3) - 4,
				".xpm", 4))
			exit_error("Invalid extension to a texture's path", scene);
		check_texture(scene);
	}
	if (check_id(scene->line, 1))
	{
		if (ft_strchr_count(scene->line + 2, ',') != 2)
			exit_error("Syntax error: the Floor/Ceiling colors needs to be separated by ','",
				scene);
		check_fc(scene, 1, 0, 0);
	}
}
