/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_row_aux_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 16:31:23 by efinda            #+#    #+#             */
/*   Updated: 2025/04/30 14:43:33 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

t_point	rows_size(t_row *head)
{
	t_row	*tmp;
	t_point	size;

	if (!head)
		return ((t_point){0, 0});
	size = (t_point){0, 0};
	tmp = head;
	while (tmp)
	{
		if (ft_strlen(tmp->str) > size.x)
			size.x = ft_strlen(tmp->str);
		tmp = tmp->next;
		size.y++;
	}
	return (size);
}

char	**row_to_mtx(t_row *head)
{
	char	**mtx;
	int		i;

	if (!head)
		return (NULL);
	mtx = (char **)malloc(sizeof(char *) * (rows_size(head).y + 1));
	if (!mtx)
		return (NULL);
	i = 0;
	while (head)
	{
		mtx[i] = ft_strdup(head->str);
		head = head->next;
		i++;
	}
	mtx[i] = NULL;
	return (mtx);
}

t_row	*get_last_row(t_row *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}
