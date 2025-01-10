/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:36:43 by efinda            #+#    #+#             */
/*   Updated: 2025/01/10 01:21:12 by efinda           ###   ########.fr       */
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

static int	check_element(t_cub *cub, int *i, int error)
{
	cub->tmp = ft_strtrim(cub->line, " ");
	ft_strfree(&cub->line);
	ft_swaptr((void **)&cub->line, (void **)&cub->tmp);
	if (!ft_strchr(cub->line, ' ') || (check_id(cub->line, 1)
			&& (ft_strchr_count(cub->line + 2, ',') != 2))
		|| (ft_strlen(cub->line) > 5 && check_id(cub->line, 0)
			&& !ft_strnstr(cub->line, " ./", ft_strlen(cub->line))))
        error++;
	if (check_id(cub->line, 1))
		error = check_fc(cub, -1, 0, 0);
	else if (check_id(cub->line, 0))
		error = check_texture(cub + 3, -1, 0, 0);
    if (error)
    {
		ft_strfree(&cub->line);
        return (1);
    }
    return (0);
}

void	check_elements(t_cub *cub, int i)
{
	while (-42 && i != 6)
	{
		cub->line = get_next_line(cub->fd);
		if (!cub->line)
			break ;
        cub->line[ft_strlen(cub->line) - 1] = '\0';
		if (!*cub->line || ft_strspace(cub->line))
		{
			ft_strfree(&cub->line);
			continue ;
		}
		if (check_element(cub, &i, 0))
		{
			ft_putstr_fd("Error\n\tInvalid element in the file\n", 2);
			exit(1);
		}
	}
	if (i < 8)
	{
		ft_putstr_fd("Error\nMissing elements\n", 2);
		exit(1);
	}
}
