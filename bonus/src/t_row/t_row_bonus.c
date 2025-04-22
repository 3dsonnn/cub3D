/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_row_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 16:18:27 by efinda            #+#    #+#             */
/*   Updated: 2025/04/22 15:34:24 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

t_row	*new_row(char *str)
{
	t_row	*row;

	row = (t_row *)malloc(sizeof(t_row));
	if (!row)
		return (NULL);
	row->str = ft_strdup(str);
	row->next = NULL;
	return (row);
}

void	free_rows(t_row **head)
{
	t_row	*tmp;

	if (!head || !*head)
		return ;
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		ft_strfree(&tmp->str);
		free(tmp);
	}
	*head = NULL;
}

char	**row_to_mtx(t_row *head)
{
	char	**mtx;
	t_row	*tmp;
	int		i;

	if (!head)
		return (NULL);
	mtx = (char **)malloc(sizeof(char *) * (rowlen(head) + 1));
	if (!mtx)
		return (NULL);
	i = 0;
	tmp = head;
	while (tmp)
	{
		mtx[i] = ft_strdup(tmp->str);
		tmp = tmp->next;
		i++;
	}
	mtx[i] = NULL;
	return (mtx);
}
