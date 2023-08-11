/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 20:05:40 by vzhadan           #+#    #+#             */
/*   Updated: 2023/01/28 15:08:44 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 *	Compares up to num characters of the string {s1} to those of the string {s2}.
 *	This function starts comparing the first character of each string. 
 *	If they are equal to each other, 
 *	it continues with the following pairs until the characters differ,
 *	until a terminating null-character is reached, 
 *	or until num characters match in both strings, whichever happens first.
 *  If strings are equal returns 0.
*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (i < n && (*(s1 + i) || *(s2 + i)))
	{
		if (*(s1 + i) != *(s2 + i))
			return ((*(str1 + i) - *(str2 + i)));
		i++;
	}
	return (0);
}
