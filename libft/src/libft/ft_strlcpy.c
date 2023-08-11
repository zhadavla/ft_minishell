/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:03:47 by vzhadan           #+#    #+#             */
/*   Updated: 2023/01/28 15:07:45 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 *	The contents of string {src} are copied into buffer {dst}.
 *	Only {size} characters maximum are copied,
 *	and the value returned is the size of string {src}.
 *	(The value returned is always the size of string {src},
 *	regardless of how many characters are copied.)
*/
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			len;

	len = 0;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (size > 0)
	{
		while (--size && *(s + len))
		{
			*(d + len) = *(s + len);
			len++;
		}
		*(d + len) = 0;
	}
	while (*(src + len))
		len++;
	return (len);
}
