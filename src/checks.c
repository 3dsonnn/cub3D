/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:00:49 by efinda            #+#    #+#             */
/*   Updated: 2025/01/09 21:28:00 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	check_map(t_cub *cub)
{
	char	*line;
	int		i;

	i = 0;
	check_elements(cub);
	cub->fd = open(av[1], O_RDONLY);
	while (get_next_line(fd, &line))
	{
		if (line[0] == 'R')
			get_resolution(cub, line);
		else if (line[0] == 'F' || line[0] == 'C')
			get_fc(cub, line);
		else if (line[0] == 'N' || line[0] == 'S' || line[0] == 'W'
			|| line[0] == 'E')
			get_wall(cub, line);
		else if (line[0] == '1' || line[0] == ' ')
			i++;
		free(line);
	}
	if (i == 0)
	{
		ft_putstr_fd("Error\nInvalid map\n", 2);
		exit(1);
	}
}

static int	check_element(t_cub *cub, int *i)
{
	cub->tmp = ft_strtrim(cub->line, " ");
	ft_strfree(&cub->line);
	cub->line = cub->tmp;
	if (!ft_strchr(cub->line, ' ') || ((*cub->line == 'F' || *cub->line == 'C')
			&& (cub->line[1] != ' ' || ft_strchr_count(cub->line, ',') != 2))
		|| (*cub->line != 'F' && *cub->line != 'C' && (ft_strlen(cub->line) < 6
				|| cub->line[2] != ' ' || !ft_strnstr(cub->line, " ./",
					ft_strlen(cub->line)))))
	{
		ft_strfree(&cub->line);
		return (1);
	}
}

static void	check_elements(t_cub *cub, int i)
{
	while (-42 && i != 6)
	{
		cub->line = get_next_line(cub->fd);
		if (!cub->line)
			break ;
		if (*cub->line == '\n' || ft_strspace(cub->line))
		{
			ft_strfree(&cub->line);
			continue ;
		}
		if (check_element(cub, &i))
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

void	checks(t_cub *cub, int ac, char **av)
{
	if (ac != 2)
	{
		ft_putstr_fd("Error\n\tInvalid number of arguments\n", 2);
		exit(1);
	}
	if (ft_strlen(av[1]) <= 4 || ft_strncmp(av[1] + ft_strlen(av[1]) - 4,
			".cub", 4))
	{
		ft_putstr_fd("Error\n\tInvalid file extension\n", 2);
		exit(1);
	}
	cub->fd = open(av[1], O_RDONLY);
	if (cub->fd < 0)
	{
		ft_dprintf(2, "Error\n\t%s\n", strerror(errno));
		exit(1);
	}
	cub->line = get_next_line(cub->fd);
	if (!cub->line)
	{
		ft_putstr_fd("Error\n\tEmpty file\n", 2);
		exit(1);
	}
	ft_strfree(&cub->line);
	check_elements(cub, 0);
}
