/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_map_crd_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:40:25 by efinda            #+#    #+#             */
/*   Updated: 2025/04/24 14:43:53 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D_bonus.h"

t_map_crd	*new_map_crd(char c, char *col, char *line)
{
	t_map_crd	*map_crd;
	t_strs		tmp;

	map_crd = (t_map_crd *)malloc(sizeof(t_map_crd));
	if (!map_crd)
	{
		ft_strfree(&col);
		return (NULL);
	}
	tmp = (t_strs){.s1 = ft_strjoin("\tLine: ", line, 0),
		.s2 = ft_strdup(" | "),
		.s3 = ft_strjoin("Column: ", col, 2),
		.s4 = ft_strdup(" | "),
		.s5 = ft_strjoin("Char: ", ft_strdup((char []){c, '\0'}), 2),
		.s6 = ft_strdup("\n")};
	*map_crd = (t_map_crd){.str = join_strs(tmp), .next = NULL};
	return (map_crd);
}

void	add_map_crd(t_map_crd **head, t_map_crd *new)
{
	t_map_crd	*tmp;

	if (!head || !new)
		return ;
	tmp = *head;
	if (!tmp)
		*head = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	free_map_crds(t_map_crd **head)
{
	t_map_crd	*tmp;

	if (!head || !*head)
		return ;
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		ft_strfree(&tmp->str);
		free(tmp);
	}
	*head = NULL;
}

char	*map_crds_to_str(t_map_crd *head, char *base)
{
	char	*res;

	res = NULL;
	if (!head && !base)
		return (NULL);
	if (!head)
		return (ft_strdup(base));
	if (base)
		res = ft_strjoin(base, (char []){'\n', '\0'}, 0);
	while (head)
	{
		res = ft_strjoin(res, head->str, 1);
		head = head->next;
	}
	res[ft_strlen(res) - 1] = '\0';
	return (res);
}
