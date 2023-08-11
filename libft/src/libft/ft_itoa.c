/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:34:32 by vzhadan           #+#    #+#             */
/*   Updated: 2023/01/31 17:05:40 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 *	Function get_num_of_digits returns number of digits in the number
*/
size_t	get_num_of_digits(int n)
{
	size_t	num;

	num = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		num++;
	}
	while (n > 0)
	{
		num++;
		n /= 10;
	}
	return (num);
}

/*
 *	Makes string representation of the number,
 * 	allocates memory for the string and returns it. 
*/
char	*ft_itoa(int n)
{	
	char	*str_num;
	size_t	num_of_digits;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	num_of_digits = get_num_of_digits(n);
	str_num = (char *)malloc((num_of_digits + 1) * sizeof(char));
	if (!str_num)
		return (NULL);
	str_num[num_of_digits--] = 0;
	if (n == 0)
		return (ft_strdup("0"));
	if (n < 0)
	{
		str_num[0] = '-';
		n *= -1;
	}
	while (n > 0)
	{
		str_num[num_of_digits] = n % 10 + '0';
		n /= 10;
		num_of_digits--;
	}
	return (str_num);
}
