/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 08:03:21 by efinda            #+#    #+#             */
/*   Updated: 2025/05/02 16:39:14 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static	void	ft_strjoin_free(char *str, char *buffer, int flag)
{
	if (flag == 1)
		ft_strfree(&str);
	if (flag == 2)
		ft_strfree(&buffer);
	if (flag == 3)
	{
		ft_strfree(&str);
		ft_strfree(&buffer);
	}
}

char	*ft_strjoin(char *str, char *buffer, int flag)
{
	char	*new_str;
	int		lens;

	if (!str && !buffer)
		return (NULL);
	if (!str)
		new_str = ft_strdup(buffer);
	else if (!buffer)
		new_str = ft_strdup(str);
	else
	{
		lens = ft_strlen(str) + ft_strlen(buffer);
		new_str = (char *)malloc(sizeof(char) * (lens + 1));
		if (!new_str)
			return (NULL);
		ft_join(&new_str, str, buffer);
	}
	ft_strjoin_free(str, buffer, flag);
	return (new_str);
}
