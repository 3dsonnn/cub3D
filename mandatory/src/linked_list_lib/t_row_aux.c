/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_row_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:20:30 by efinda            #+#    #+#             */
/*   Updated: 2025/05/01 14:19:46 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

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
