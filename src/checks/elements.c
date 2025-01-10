/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:36:43 by efinda            #+#    #+#             */
/*   Updated: 2025/01/10 05:05:46 by efinda           ###   ########.fr       */
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

static void	check_color_range(t_cub *cub, int len, int rgb[3])
{
	cub->tmp = cub->line;
	len = ft_strlen(cub->line);
	if (*cub->line == ',' || len < 5 || len > 11 || cub->line[len - 1] == ',')
		exit_error("Syntax error in a file element", cub->line, NULL);
	*rgb = ft_atoi(cub->line);
	cub->line = ft_strchr(cub->line, ',');
	if (*(cub->line + 1) == ',')
		exit_error("Syntax error in a file element", cub->tmp, NULL);
	rgb[1] = ft_atoi(cub->line + 1);
	cub->line = ft_strchr(cub->line, ',');
	rgb[2] = ft_atoi(cub->line + 1);
	ft_strfree(&cub->tmp);
	if (!(*rgb >= 0 && *rgb <= 255) || !(rgb[1] >= 0
				&& rgb[1] <= 255) || !(rgb[2] >= 0 && rgb[2] <= 255))
		exit_error("Color out of range in a file element", cub->tmp, NULL);
}

static void	check_fc(t_cub *cub, int i, int j, int len)
{
	int	rgb[3];

	while (cub->line[++i])
		if (cub->line[i] != ',' && cub->line[i] != ' ' && !(cub->line[i] >= '0'
				&& cub->line[i] <= '9'))
			exit_error("Syntax error in a file element", cub->line, NULL);
	cub->mtx = ft_split(cub->line, ' ');
	len = ft_mtxlen(cub->mtx);
	if (len < 1 || len > 5 || strcmp(*cub->mtx, ",") == 0 || strcmp(cub->mtx[len
			- 1], ",") == 0)
		exit_error("Syntax error in a file element", cub->line, cub->mtx);
	ft_strfree(&cub->line);
	while (cub->mtx[++j])
		cub->line = ft_strjoin_free(cub->line, cub->mtx[j]);
	ft_mtxfree(&cub->mtx);
	check_color_range(cub, 0, rgb);
}

static void	check_texture(t_cub *cub)
{
	cub->tmp = ft_strtrim(cub->line + 3, " ");
	ft_strfree(&cub->line);
	ft_swaptr((void **)&cub->line, (void **)&cub->tmp);
	if (ft_word_count(cub->line, ' ') != 1)
		exit_error("Invalid path to a texture element: It cannot contain spaces", cub->line, NULL);
	if (open(cub->line, O_RDONLY) < 0)
	{
		ft_strfree(&cub->line);
		cub->line = ft_strjoin("Invalid path to a texture element: ", strerror(errno));
		exit_error(cub->line, cub->line, NULL);
	}
	ft_strfree(&cub->line);
}

void	check_element(t_scene *scene)
{
	scene->tmp = ft_strtrim(scene->line, " ");
	ft_strfree(&scene->line);
	ft_swaptr((void **)&scene->line, (void **)&scene->tmp);
	if (!ft_strchr(scene->line, ' ') || (check_id(scene->line, 1)
			&& ft_strchr_count(scene->line + 2, ',') != 2))
		exit_error("Invalid element in the file", scene->line, NULL);
	if (check_id(scene->line, 1))
		check_fc(scene, 1, -1, 0);
	else if (check_id(scene->line, 0))
		check_texture(scene);
	else
		exit_error("Invalid element in the file", scene->line, NULL);
}
