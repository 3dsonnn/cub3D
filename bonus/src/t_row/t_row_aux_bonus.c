/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_row_aux_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 16:31:23 by efinda            #+#    #+#             */
/*   Updated: 2025/03/04 17:33:24 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

void	add_row(t_rows **head, t_rows *_new)
{
	t_rows	*tmp;

	if (!head || !_new)
		return ;
	tmp = *head;
	if (!tmp)
		*head = _new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = _new;
	}
}

int	rowlen(t_rows *head)
{
	int		len;
	t_rows	*tmp;

	len = 0;
	tmp = head;
	if (!tmp)
		return (0);
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}
