/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:20:30 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/17 20:04:32 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

/*
 *	Finds len of string pointed by {s}
*/
size_t	ft_strlen(const char *s)
{
	unsigned int	len;

	len = 0;
	while (*(s + len))
		len++;
	return (len);
}
