/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_aux_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:01:29 by efinda            #+#    #+#             */
/*   Updated: 2025/05/05 09:19:44 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

void	update_map(t_map *map, t_row *head)
{
	t_point	iter;

	iter.y = 0;
	map->size.x = ft_strlen(head->str);
	while (head)
	{
		iter.x = -1;
		while (head->str[++iter.x])
		{
			if (head->str[iter.x] == map->start)
			{
				map->spos = (t_point){.x = iter.x, .y = iter.y};
				return ;
			}
		}
		iter.y++;
		head = head->next;
	}
}

void	extend_map(t_map *map, t_row **head, t_row *tmp)
{
	char	*aux;
	int		i;

	i = -1;
	while (tmp)
	{
		tmp->str = ft_strjoin("!!!!!", tmp->str, 2);
		tmp->str = ft_strjoin(tmp->str, "!!!!!", 1);
		tmp = tmp->next;
	}
	aux = ft_strdup((*head)->str);
	ft_memset(aux, '!', ft_strlen(aux));
	while (++i < 5)
	{
		add_row_front(head, new_row(aux, 0));
		add_row_back(head, new_row(aux, 0));
	}
	map->size = (t_point){.x = map->size.x + 10, .y = map->size.y + 10};
	map->spos = (t_point){.x = map->spos.x + 5, .y = map->spos.y + 5};
	ft_strfree(&aux);
}
