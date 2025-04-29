/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn_rev.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:05:35 by efinda            #+#    #+#             */
/*   Updated: 2025/04/28 18:12:51 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strspn_rev(char *s, char *accept)
{
	int	i;
	int	res;

	if (!s || !accept || !*s || !*accept)
		return (0);
    res = 0;
    i = ft_strlen(s);
	while (--i >= 0)
    {
		if (!ft_strchr(accept, s[i]))
			break ;
        res++;
    }
	return (res);
}
