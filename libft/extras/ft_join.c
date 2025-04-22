/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 10:35:46 by efinda            #+#    #+#             */
/*   Updated: 2025/04/22 10:56:46 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_join(char **new_str, char *str, char *buffer)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!new_str || !*new_str)
		return ;
	while (str && str[i])
	{
		(*new_str)[i] = str[i];
		i++;
	}
	while (buffer && buffer[j])
	{
		(*new_str)[i + j] = buffer[j];
		j++;
	}
	(*new_str)[i + j] = '\0';
}