/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_row_aux_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 16:31:23 by efinda            #+#    #+#             */
/*   Updated: 2025/04/24 14:44:05 by efinda           ###   ########.fr       */
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
	t_row	*tmp;
	int		i;

	if (!head)
		return (NULL);
	mtx = (char **)malloc(sizeof(char *) * (rows_size(head).y + 1));
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

void	trim_rows(t_row **head)
{
	t_row	*tmp;
	t_row	*aux;

	if (!head || !*head)
		return ;
	while (*head && ft_strspace((*head)->str))
	{
		tmp = *head;
		*head = (*head)->next;
		free_row(&tmp, tmp);
	}
	if (!*head)
		return ;
	tmp = *head;
	while (tmp->next && !ft_strspace(tmp->next->str))
		tmp = tmp->next;
	while (tmp->next && ft_strspace(tmp->next->str))
	{
		aux = tmp->next;
		tmp->next = aux->next;
		if (aux->next)
			aux->next->prev = tmp;
		free_row(&aux, aux);
	}
}

t_row	*get_last_row(t_row *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}
