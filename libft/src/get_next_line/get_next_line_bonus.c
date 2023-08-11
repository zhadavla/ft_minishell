/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:14:59 by mnurlybe          #+#    #+#             */
/*   Updated: 2023/08/11 15:51:43 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*clean_tmp(char *tmp)
{
	char	*new_tmp;
	int		i;
	int		j;

	i = 0;
	while (tmp[i] != '\0' && tmp[i] != '\n')
		i++;
	if (tmp[i] == 0)
	{
		free(tmp);
		return (0);
	}
	new_tmp = ft_calloc((ft_strlen(tmp) - i + 1), sizeof(char));
	if (!new_tmp)
		return (0);
	j = 0;
	i++;
	while (tmp[i] != '\0')
	{
		new_tmp[j] = tmp[i];
		j++;
		i++;
	}
	free (tmp);
	return (new_tmp);
}

char	*get_line(char *tmp)
{
	char	*line;
	int		i;
	int		j;

	if (!tmp[0])
		return (NULL);
	j = 0;
	while (tmp[j] != '\0' && tmp[j] != '\n')
		j++;
	j++;
	line = ft_calloc(j + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (tmp[i] != '\0' && tmp[i] != '\n')
	{
		line[i] = tmp[i];
		i++;
	}
	if (tmp[i] == '\0')
		line[i] = '\0';
	else
		line[i] = '\n';
	return (line);
}

char	*get_tmp(int fd, char *tmp)
{
	char	*buf;
	int		read_bytes;

	if (!tmp)
		tmp = ft_calloc(1, sizeof(char));
	read_bytes = 1;
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	while (!is_strchr(tmp, '\n') && read_bytes > 0)
	{
		read_bytes = (int)read(fd, buf, BUFFER_SIZE);
		if (read_bytes == 0)
			break ;
		if (read_bytes == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[read_bytes] = '\0';
		tmp = ft_strjoin(tmp, buf);
	}
	free(buf);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*tmp[2048];
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, &line, 0) < 0)
		return (NULL);
	tmp[fd] = get_tmp(fd, tmp[fd]);
	if (!tmp[fd])
		return (NULL);
	line = get_line(tmp[fd]);
	tmp[fd] = clean_tmp(tmp[fd]);
	return (line);
}
