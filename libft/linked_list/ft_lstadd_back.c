/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:53:07 by efinda            #+#    #+#             */
/*   Updated: 2025/01/12 09:26:56 by marcsilv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstadd_back(t_list **lst, t_list *newnode)
{
	t_list	*tmp;

	if (!(*lst))
		*lst = newnode;
	else
	{
		tmp = ft_lstlast(*lst);
		tmp->next = newnode;
	}
}
