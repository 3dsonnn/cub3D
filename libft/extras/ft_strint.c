/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 20:03:17 by efinda            #+#    #+#             */
/*   Updated: 2025/04/25 10:25:15 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strint(char *str)
{
	int	sig;
	int	len;

	sig = 0;
	if (!ft_strnbr(str))
		return (0);
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sig = 1;
		str++;
	}
	while (*str == '0')
		str++;
	len = ft_strlen(str);
	if (len > 10)
		return (0);
	if (len == 10)
		if ((sig == 0 && ft_strcmp(str, "2147483647") > 0) || (sig == 1
				&& ft_strcmp(str, "2147483648") > 0))
			return (0);
	return (1);
}
