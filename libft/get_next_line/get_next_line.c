/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinda <efinda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:57:28 by efinda            #+#    #+#             */
/*   Updated: 2025/04/22 10:46:36 by efinda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static	char	*one_line(char *str)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	j = 0;
	if (!str || !*str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	new_line = (char *)malloc(sizeof(char) * (i + 1));
	if (!new_line)
		return (NULL);
	while (j < i)
	{
		new_line[j] = str[j];
		j++;
	}
	new_line[j] = '\0';
	return (new_line);
}

static	char	*ft_substr_gnl(char *str, int start, int end)
{
	char	*res;
	int		i;
	int		dif;

	i = 0;
	dif = end - start;
	if (dif == 0 || !str)
	{
		ft_strfree(&str);
		return (NULL);
	}
	res = (char *)malloc(sizeof(char) * (dif + 1));
	if (!res)
		return (NULL);
	while (str[start])
	{
		res[i] = str[start];
		start++;
		i++;
	}
	res[i] = '\0';
	ft_strfree(&str);
	return (res);
}

static	void	gnl_free(char *str, char *buffer)
{
	ft_strfree(&str);
	ft_strfree(&buffer);
}

char	*get_next_line(int fd)
{
	static char	*str[FD_MAX];
	char		*buffer;
	int			bytes_read;

	bytes_read = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (bytes_read && !ft_strchr(str[fd], '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (gnl_free(str[fd], buffer), NULL);
		buffer[bytes_read] = '\0';
		str[fd] = ft_strjoin(str[fd], buffer, 1);
	}
	ft_strfree(&buffer);
	buffer = one_line(str[fd]);
	str[fd] = ft_substr_gnl(str[fd], ft_strlen(buffer), ft_strlen(str[fd]));
	if (buffer && *buffer && buffer[ft_strlen(buffer) - 1] == '\n')
		buffer[ft_strlen(buffer) - 1] = '\0';
	return (buffer);
}
