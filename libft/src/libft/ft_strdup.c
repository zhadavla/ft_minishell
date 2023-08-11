/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 18:15:52 by vzhadan           #+#    #+#             */
/*   Updated: 2023/01/28 15:06:40 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 *	This function returns a pointer to a null-terminated byte string,
 *	which is a duplicate of the string pointed to by {s}. 
 *	The memory obtained is done dynamically using malloc 
 *	and hence it can be freed using free(). 
*/
char	*ft_strdup(const char *s)
{
	char	*new_str;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s);
	new_str = malloc(sizeof(char) * len + 1);
	if (!new_str)
		return (NULL);
	while (i <= len)
	{
		*(new_str + i) = (char )s[i];
		i++;
	}
	*(new_str + len) = 0;
	return (new_str);
}
