/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:22:14 by vzhadan           #+#    #+#             */
/*   Updated: 2023/01/31 16:57:10 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 *	Finds number of words getted from string {s} splitted by delimited {c}.
*/
size_t	get_size(char const *s, char c)
{
	size_t	size;

	size = 0;
	while (*(s))
	{
		if (*s != c && *(s + 1) == c && *(s + 1))
			size++;
		s++;
	}
	return (size + 1);
}

/*
 *	Finds how many non-{c} characters are in {s_moved} before {c} character.
*/
size_t	find_len_of_word(char const *s_moved, char c)
{
	size_t	len;

	len = 0;
	while (s_moved[len] && s_moved[len] != c)
		len++;
	return (len);
}

/*
 *	Allocates memory for word (substring getted form {s_moved} 
 *	as string before first occurence of {c} in {s_moved}) 
 *	and adds word to {str_indx} array, increments {indx}. 
*/
void	add_word(char **str_indx, char const *s_moved, char c, size_t *indx)
{
	size_t	len_of_word;

	len_of_word = find_len_of_word(s_moved, c);
	*str_indx = (char *)malloc(sizeof(char) * (len_of_word + 1));
	if (!str_indx)
	{
		*str_indx = NULL;
		return ;
	}
	ft_strlcpy(*str_indx, s_moved, len_of_word + 1);
	*indx = *indx + 1;
}

/*
 *	Allocates with malloc() and returns an array
 *	of strings obtained by splitting {s} using the
 *	character {c} as a delimiter. The array must end
 *	with a NULL pointer.
*/
char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	indx;
	int		is_start;

	if (!s)
		return (NULL);
	is_start = 1;
	indx = 0;
	str = (char **)malloc(sizeof(char *) * (get_size(s, c) + 1));
	if (!str)
		return (NULL);
	while (*s)
	{
		if (is_start && *s != c)
		{
			is_start = 0;
			add_word(&str[indx], s, c, &indx);
		}
		else if (*s == c && *(s + 1) != c && *(s + 1) && !is_start)
			add_word(&str[indx], s + 1, c, &indx);
		s++;
	}
	str[indx] = NULL;
	return (str);
}
