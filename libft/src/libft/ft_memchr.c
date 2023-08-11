/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 20:14:08 by vzhadan           #+#    #+#             */
/*   Updated: 2023/01/28 14:00:16 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 *	Searches for the first occurrence of the character {c} (an unsigned char) 
 *	in the first {n} bytes of the string pointed to, by the argument {str}.
*/
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (n--)
	{
		if (*(str) == (unsigned char )c)
			return (str);
		str++;
	}
	return (NULL);
}	
