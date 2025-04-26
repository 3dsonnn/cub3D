/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:10:08 by efinda            #+#    #+#             */
/*   Updated: 2025/04/25 12:56:06 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

char	*join_strs(t_strs strs)
{
	char	*res;

	res = NULL;
	if (strs.s1)
		res = ft_strjoin(res, strs.s1, 3);
	if (strs.s3)
		res = ft_strjoin(res, strs.s2, 3);
	if (strs.s3)
		res = ft_strjoin(res, strs.s3, 3);
	if (strs.s4)
		res = ft_strjoin(res, strs.s4, 3);
	if (strs.s5)
		res = ft_strjoin(res, strs.s5, 3);
	if (strs.s6)
		res = ft_strjoin(res, strs.s6, 3);
	return (res);
}
