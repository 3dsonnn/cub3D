/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:00:49 by efinda            #+#    #+#             */
/*   Updated: 2025/01/10 04:11:27 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static	void	check_args(t_scene *scene, int ac, char **av)
{
	if (ac != 2)
		exit_error("Invalid number of arguments", NULL, NULL);
	if (ft_strlen(av[1]) <= 4 || ft_strncmp(av[1] + ft_strlen(av[1]) - 4,
			".cub", 4))
		exit_error("Invalid scene file extension", NULL, NULL);
	scene->fd = open(av[1], O_RDONLY);
	if (scene->fd < 0)
		exit_error(strerror(errno), NULL, NULL);
	scene->line = get_next_line(scene->fd);
	if (!scene->line)
		exit_error("Empty scene file", NULL, NULL);
	ft_strfree(&scene->line);
}

static	void	check_elements(t_scene *scene, int i)
{
	while (-42 && i != 6)
	{
		scene->line = get_next_line(scene->fd);
		if (!scene->line)
			exit_error("The scene file is incomplete", NULL, NULL);
		scene->line[ft_strlen(scene->line) - 1] = '\0';
		if (!*scene->line || ft_strspace(scene->line))
		{
			ft_strfree(&scene->line);
			continue ;
		}
		check_element(scene);
        i++;
	}
	if (i != 6)
		exit_error("Missing elements in the scene file", NULL, NULL);
}

static	void	check_map(t_scene *scene)
{
	char	*line;
	int		i;

	i = 0;
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

void	checks(t_scene *scene, int ac, char **av)
{
	check_args(scene, ac, av);
	check_elements(scene, 0);
	check_map(scene);
}
