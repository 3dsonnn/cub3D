/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 19:27:48 by efinda            #+#    #+#             */
/*   Updated: 2025/03/04 06:45:20 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static int	all_space(char **map, int i)
{
	while (map[++i])
		if (ft_strspn(map[i], " ") != ft_strlen(map[i]))
			return (0);
	return (1);
}

static int	get_indexes(char **map, int *begin, int *end)
{
	while (map[++(*begin)] && (ft_strspn(map[(*begin)],
				" ") == ft_strlen(map[(*begin)])))
		;
	while (map[--(*end)] && (ft_strspn(map[(*end)],
				" ") == ft_strlen(map[(*end)])))
		;
	if (!*begin && !map[*end + 1])
		return (1);
	return (0);
}

void	trimap(char ***map, int begin, int end, t_iter iter)
{
	char	**new;

	if (!map || !(*map) || !(*map)[0] || all_space(*map, -1))
		return ;
	end = ft_mtxlen(*map);
	if (get_indexes(*map, &begin, &end))
		return ;
	new = (char **)malloc(sizeof(char *) * (end - begin + 2));
	if (!new)
		return ;
	while (begin - 1 != end)
	{
		new[iter.i] = ft_strdup((*map)[begin]);
		iter.i++;
		begin++;
	}
	new[iter.i] = NULL;
	ft_mtxfree(map);
	*map = new;
}
