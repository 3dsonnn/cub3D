/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_row_trim_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:24:03 by efinda            #+#    #+#             */
/*   Updated: 2025/05/01 14:25:31 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

void	trim_rows_vertically(t_row **head)
{
	t_row	*tmp;
	t_row	*aux;

	if (!head || !*head)
		return ;
	while (*head && ft_strspace((*head)->str))
	{
		tmp = *head;
		*head = (*head)->next;
		if (*head)
			(*head)->prev = NULL;
		free_row(&tmp);
	}
	if (!*head)
		return ;
	tmp = get_last_row(*head);
	while (tmp && ft_strspace(tmp->str))
	{
		aux = tmp;
		tmp = tmp->prev;
		if (tmp)
			tmp->next = NULL;
		free_row(&aux);
	}
}

t_point	get_horizontal_limits(t_row *head)
{
	t_point	tmp;
	t_point	res;

	if (!head)
		return ((t_point){0, 0});
	tmp = (t_point){0, 0};
	res = (t_point){INT_MAX, INT_MAX};
	while (head)
	{
		tmp.x = ft_strspn(head->str, " ");
		tmp.y = ft_strspn_rev(head->str, " ");
		if (tmp.x < res.x)
			res.x = tmp.x;
		if (tmp.y < res.y)
			res.y = tmp.y;
		head = head->next;
	}
	return (res);
}

void	trim_rows_horizontally(t_row **head, t_point limits)
{
	t_row	*tmp;
	char	*aux;
	int		len;

	if (!head || !*head || limits.x < 0 || limits.y < 0 || (!limits.x
			&& !limits.y))
		return ;
	tmp = *head;
	while (tmp)
	{
		len = ft_strlen(tmp->str);
		if (len >= (limits.x + limits.y))
		{
			tmp->str[len - limits.y] = '\0';
			aux = ft_strdup(tmp->str + limits.x);
			if (aux)
			{
				ft_swaptr((void **)&tmp->str, (void **)&aux);
				ft_strfree(&aux);
			}
		}
		tmp = tmp->next;
	}
}
