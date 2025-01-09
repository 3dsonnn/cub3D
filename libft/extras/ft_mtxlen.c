/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mtxlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 19:02:27 by efinda            #+#    #+#             */
/*   Updated: 2024/11/09 19:07:12 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_mtxlen(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix || !(*matrix))
		return (0);
	while (matrix[i])
		i++;
	return (i);
}
