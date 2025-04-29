/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 06:42:11 by efinda            #+#    #+#             */
/*   Updated: 2025/04/28 18:12:33 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strspn(char *s, char *accept)
{
	int	i;

	i = -1;
	if (!s || !accept || !*s || !*accept)
		return (0);
	while (s[++i])
		if (!ft_strchr(accept, s[i]))
			break ;
	return (i);
}
