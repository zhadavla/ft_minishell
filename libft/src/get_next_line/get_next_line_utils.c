/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 15:07:21 by mnurlybe          #+#    #+#             */
/*   Updated: 2023/09/17 20:04:05 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/get_next_line.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*s_ptr;
	size_t			i;

	i = 0;
	s_ptr = (unsigned char *)s;
	while (i < n)
	{
		s_ptr[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem_ptr;

	mem_ptr = malloc(nmemb * size);
	if (!mem_ptr)
		return (0);
	ft_bzero(mem_ptr, nmemb * size);
	return (mem_ptr);
}

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (s[count] != '\0')
		count++;
	return (count);
}


char	*ft_strjoin(char *tmp, char *buf)
{
	char	*join;
	int		i;
	int		j;

	join = malloc(sizeof(char) * (ft_strlen(tmp) + ft_strlen(buf)) + 1);
	if (!join || !buf || !tmp)
		return (0);
	i = 0;
	while (tmp[i] != 0)
	{
		join[i] = tmp[i];
		i++;
	}
	j = 0;
	while (buf[j] != 0)
	{
		join[i] = buf[j];
		i++;
		j++;
	}
	join[ft_strlen(tmp) + ft_strlen(buf)] = '\0';
	free(tmp);
	return (join);
}
