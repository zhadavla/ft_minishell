/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 19:17:49 by vzhadan           #+#    #+#             */
/*   Updated: 2023/01/28 15:07:22 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 *	Appends {src} to string {dst}. 
 *	({size} is the full size of {dst}, not space left)
 *	At most {size}-1 characters will be copied.
 *  Always NULL terminates (unless {size} <= strlen(dst)).
 *	Returns strlen(src) + MIN(dsize, strlen(initial dst)).
 *	If retval >= {size}, truncation occurred.
*/
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	len = 0;
	if (!dst && !size)
		return (0);
	while (*(dst + len) && len < size)
		len ++;
	i = len;
	while (*(src + len - i) && (len + 1 < size))
	{
		*(dst + len) = *(src + len - i);
		len ++;
	}
	if (i < size)
		*(dst + len) = 0;
	return (i + ft_strlen(src));
}
