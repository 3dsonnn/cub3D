/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_row_trim_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 19:58:29 by efinda            #+#    #+#             */
/*   Updated: 2025/04/28 19:58:50 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

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

t_point	get_horizontal_limits(t_row *head, t_point limits, t_point tmp)
{
	if (!head)
		return ((t_point){0, 0});
	while (head)
	{
		tmp.x = ft_strspn(head->str, " ");
		tmp.y = ft_strspn_rev(head->str, " ");
		if (tmp.x < limits.x)
			limits.x = tmp.x;
		if (tmp.y < limits.y)
			limits.y = tmp.y;
		head = head->next;
	}
	return (limits);
}

void	trim_rows_horizontally(t_row **head, t_point limits)
{
	t_row	*tmp;
	char	*aux;

	if (!head || !*head || (!limits.x && !limits.y))
		return ;
	tmp = *head;
	while (tmp)
	{
		aux = ft_strdup(tmp->str + limits.x);
		if (aux)
		{
			aux[ft_strlen(aux) - limits.y] = '\0';
			ft_swaptr((void **)&tmp->str, (void **)&aux);
			ft_strfree(&aux);
		}
		tmp = tmp->next;
	}
}
