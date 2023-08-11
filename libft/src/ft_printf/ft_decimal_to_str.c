/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decimal_to_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 20:18:04 by vzhadan           #+#    #+#             */
/*   Updated: 2023/08/05 16:04:33 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 *	Makes number positive (with respect to overflow).
 *	assigns {flags->is_negative} equal to one.
*/
unsigned int	ft_make_number_positive(int num, t_flags *flags, char letter)
{
	unsigned int	u_num;

	if (num < 0)
	{
		if (letter == 'u' || letter == 'x' || letter == 'X')
			u_num = num;
		else
			u_num = num * (-1);
		flags->is_negative = 1;
	}
	else
		u_num = num;
	return (u_num);
}

char	*ft_reverse_str(char *str_num, int i)
{
	int		j;
	char	tmp;

	j = -1;
	while (++j < i / 2)
	{
		tmp = str_num[j];
		str_num[j] = str_num[i - j - 1];
		str_num[i - j - 1] = tmp;
	}
	str_num[i] = '\0';
	return (str_num);
}

char	*ft_get_base(char letter)
{
	char	*base;

	base = (char *)malloc(17 * sizeof(*base));
	if (letter == 'd' || letter == 'i' || letter == 'u')
		ft_strlcpy(base, "0123456789", 11);
	else if (letter == 'x')
		ft_strlcpy(base, "0123456789abcdef", 17);
	else if (letter == 'X')
		ft_strlcpy(base, "0123456789ABCDEF", 17);
	return (base);
}

char	*ft_number_to_str(unsigned int num, char letter, int system)
{
	char	*str_num;
	char	*base;
	int		i;

	base = NULL;
	base = ft_get_base(letter);
	str_num = (char *)malloc((ft_find_nod(num, system) + 1) * sizeof(*str_num));
	i = 0;
	if (!num)
	{
		*str_num = '0';
		str_num[1] = '\0';
		free(base);
		return (str_num);
	}
	while (num != 0)
	{
		str_num[i++] = base[num % system];
		num = num / system;
	}
	str_num = ft_reverse_str(str_num, i);
	free(base);
	return (str_num);
}

char	*ft_number_to_str_l(long long unsigned num, char letter, int system)
{
	char	*str_num;
	char	*base;
	size_t	i;

	base = ft_get_base(letter);
	str_num = (char *)malloc((ft_find_nod_l(num, system) + 1) * sizeof(char));
	i = 0;
	if (!num)
	{
		*str_num = '0';
		str_num[1] = '\0';
		free(base);
		return (str_num);
	}
	while (num != 0)
	{
		str_num[i++] = base[num % system];
		num /= system;
	}
	str_num = ft_reverse_str(str_num, i);
	free(base);
	return (str_num);
}
