/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_row.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 16:18:27 by efinda            #+#    #+#             */
/*   Updated: 2025/04/23 11:25:52 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

t_row	*new_row(char *str, int nbr)
{
	t_row	*row;

	row = (t_row *)malloc(sizeof(t_row));
	if (!row)
		return (NULL);
	*row = (t_row){.str = ft_strdup(str),
		.line_nbr = ft_itoa(nbr),
		.next = NULL, .prev = NULL};
	return (row);
}

void	add_row(t_row **head, t_row *new)
{
	t_row	*tmp;

	if (!head || !new)
		return ;
	tmp = *head;
	if (!tmp)
		*head = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

void	free_row(t_row **head, t_row *ref)
{
    t_row *cur;

    if (!head || !*head || !ref)
        return;
    cur = *head;
    while (cur && cur != ref)
        cur = cur->next;
    if (!cur)
        return ;
    if (cur == *head)
    {
        *head = cur->next;
        if (*head)
            (*head)->prev = NULL;
    }
    else
    {
        cur->prev->next = cur->next;
        if (cur->next)
            cur->next->prev = cur->prev;
    }
    ft_strfree(&ref->str);
    ft_strfree(&ref->line_nbr);
    free(ref);
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
		ft_strfree(&tmp->line_nbr);
		free(tmp);
	}
	*head = NULL;
}
