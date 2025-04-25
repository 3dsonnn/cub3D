/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 00:59:55 by efinda            #+#    #+#             */
/*   Updated: 2025/04/24 19:28:07 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strtrim(char const *str, char const *set)
{
	size_t	i;
	size_t	j;
	char	*res;

	if (!str || !set)
		return (NULL);
	if (ft_strspn((char *)str, (char *)set) == ft_strlen(str))
		return (ft_strdup(""));
	i = 0;
	j = ft_strlen(str);
	while (str[i] && ft_strchr(set, str[i]))
		i++;
	while (str[j - 1] && ft_strchr(set, str[j - 1]) && j > i)
		j--;
	res = (char *)malloc(sizeof(char) * (j - i + 1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, &str[i], j - i + 1);
	return (res);
}
