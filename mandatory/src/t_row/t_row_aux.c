/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_row_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 16:31:23 by efinda            #+#    #+#             */
/*   Updated: 2025/04/22 17:14:08 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static	int	rowlen(t_row *head)
{
	int		len;
	t_row	*tmp;

	len = 0;
	tmp = head;
	if (!tmp)
		return (0);
	while (tmp)
	{
		tmp = tmp->next;
		len++;
	}
	return (len);
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
