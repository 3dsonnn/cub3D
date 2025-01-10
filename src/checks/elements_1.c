/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 22:34:04 by efinda            #+#    #+#             */
/*   Updated: 2025/01/10 01:33:29 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

static int	check_color_range(t_cub *cub, int len, int error)
{
	len = ft_strlen(cub->tmp);
	if (*cub->tmp == ',' || len < 5 || cub->tmp[len - 1] == ',')
		error++;
    cub->tmp = ft_strchr(cub->tmp, ',');
    if (*(cub->tmp + 1) == ',')
        error++;
    cub->tmp = ft_strchr(cub->tmp + 1, ',');
    ft_strfree(&cub->tmp);
	if (error)
        return (1);
    return (0);
}

int	check_fc(t_cub *cub, int i, int len, int error)
{
	while (cub->line[++i])
		if (cub->line[i] != ',' && cub->line[i] != ' ' && !(cub->line[i] >= '0'
				&& cub->line[i] <= '9'))
			error++;
	cub->mtx = ft_split(cub->line + 2, ' ');
	len = ft_mtxlen(cub->mtx);
	if (len < 1 || len > 5 || strcmp(*cub->mtx, ",") == 0 || strcmp(cub->mtx[len
			- 1], ",") == 0)
		error++;
	i = -1;
	while (cub->mtx[++i])
		cub->tmp = ft_strjoin_free(cub->tmp, cub->mtx[i]);
	error = check_color_range(cub, 0, 0);
	ft_mtxfree(&cub->mtx);
	if (error)
	{
		ft_strfree(&cub->line);
		return (1);
	}
	return (0);
}
