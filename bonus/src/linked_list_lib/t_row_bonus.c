/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_row_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 16:18:27 by efinda            #+#    #+#             */
/*   Updated: 2025/05/01 14:24:47 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

t_row	*new_row(char *str, int nbr)
{
	t_row	*row;

	row = (t_row *)malloc(sizeof(t_row));
	if (!row)
		return (NULL);
	*row = (t_row){.str = ft_strdup(str), .line_nbr = ft_itoa(nbr),
		.next = NULL, .prev = NULL};
	return (row);
}

void	add_row_back(t_row **head, t_row *new)
{
	t_row	*tmp;

	if (!head || !new)
		return ;
	tmp = *head;
	if (!tmp)
		*head = new;
	else
	{
		tmp = get_last_row(tmp);
		tmp->next = new;
		new->prev = tmp;
	}
}

void	add_row_front(t_row **head, t_row *new)
{
	if (!head || !new)
		return ;
	if (!*head)
		*head = new;
	else
	{
		new->next = *head;
		(*head)->prev = new;
		*head = new;
	}
}

void	free_row(t_row **row)
{
	if (row && *row)
	{
		ft_strfree(&(*row)->str);
		ft_strfree(&(*row)->line_nbr);
		free(*row);
		*row = NULL;
	}
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
		free_row(&tmp);
	}
	*head = NULL;
}
