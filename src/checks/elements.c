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

static int	check_color_range(t_cub *cub, int len, int error, int rgb[3])
{
	len = ft_strlen(cub->tmp);
	if (*cub->tmp == ',' || len < 5 || len > 11 || cub->tmp[len - 1] == ',')
		error = 1;
	*rgb = ft_atoi(cub->tmp);
	cub->tmp = ft_strchr(cub->tmp, ',');
	if (*(cub->tmp + 1) == ',')
		error = 1;
	rgb[1] = ft_atoi(cub->tmp + 1);
	cub->tmp = ft_strchr(cub->tmp, ',');
	rgb[2] = ft_atoi(cub->tmp + 1);
	ft_strfree(&cub->tmp);
	if (!error && (!(*rgb >= 0 && *rgb <= 255) || !(rgb[1] >= 0
				&& rgb[1] <= 255) || !(rgb[2] >= 0 && rgb[2] <= 255)))
    {
        ft_putstr_fd("Error\n\tThere's a color out of the range in an element in the file\n", 2);
        cub->error = 1;
    }
	if (error)
		return (1);
	return (0);
}

static int	check_fc(t_cub *cub, int i, int len, int error)
{
	int	rgb[3];

	cub->line += 2;
	while (cub->line[++i])
		if (cub->line[i] != ',' && cub->line[i] != ' ' && !(cub->line[i] >= '0'
				&& cub->line[i] <= '9'))
		{
			ft_putstr_fd("Error\n\tUnknown key in the file element\n", 2);
			cub->error = 1;
			error++;
		}
	cub->mtx = ft_split(cub->line, ' ');
	len = ft_mtxlen(cub->mtx);
	if (len < 1 || len > 5 || strcmp(*cub->mtx, ",") == 0 || strcmp(cub->mtx[len
			- 1], ",") == 0)
		error++;
	i = -1;
	while (cub->mtx[++i])
		cub->tmp = ft_strjoin_free(cub->tmp, cub->mtx[i]);
	error = check_color_range(cub, 0, 0, rgb);
	ft_mtxfree(&cub->mtx);
	if (error)
		return (error);
	return (0);
}

static int	check_texture(t_cub *cub, char *line, int i, int error)
{
    char    *aux;

    aux = ft_strtrim(line, " ");
	if (ft_word_count(aux, ' ') != 1)
    {
        ft_putstr_fd("Error\n\tMore than one path to a texture element\n", 2);
        cub->error = 1;
        error = 1;
    }
	if (open(aux, O_RDONLY) < 0)
    {
        ft_putstr_fd("Error\n\tInvalid path to a texture element\n", 2);
        cub->error = 1;
        error = 1;
    }
    ft_strfree(&aux);
	if (error)
		return (1);
	return (0);
}

int	check_element(t_cub *cub, int error)
{
	cub->tmp = ft_strtrim(cub->line, " ");
	ft_strfree(&cub->line);
	ft_swaptr((void **)&cub->line, (void **)&cub->tmp);
	if (!ft_strchr(cub->line, ' ') || (check_id(cub->line, 1)
			&& ft_strchr_count(cub->line + 2, ',') != 2))
		error++;
	if (!error && check_id(cub->line, 1))
		error += check_fc(cub, -1, 0, 0);
	else if (!error && check_id(cub->line, 0))
		error += check_texture(cub, cub->line + 3, -1, 0);
	if (error)
	{
		ft_strfree(&cub->line);
		return (error);
	}
	return (0);
}
