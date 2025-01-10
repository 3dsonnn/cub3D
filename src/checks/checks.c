/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:00:49 by efinda            #+#    #+#             */
/*   Updated: 2025/01/10 01:06:34 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

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
