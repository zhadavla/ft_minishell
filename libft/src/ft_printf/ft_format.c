/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 20:18:04 by vzhadan           #+#    #+#             */
/*   Updated: 2023/08/05 16:04:33 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	format_c(va_list args, t_specifiers sp, t_flags flags)
{
	int		num;
	char	*str;

	str = malloc(2);
	*str = va_arg(args, int);
	str[1] = '\0';
	if (!str)
	{
		free(str);
		return (ft_c_s_p("(null)", &flags, &sp));
	}
	num = ft_c_s_p(str, &flags, &sp);
	free(str);
	return (num);
}

int	format_int(va_list args, t_specifiers sp, t_flags flags)
{
	int		num;
	char	*str;

	if (sp.d || sp.i)
	{
		num = va_arg(args, int);
		if (num < 0)
		{
			num *= -1;
			flags.is_negative = 1;
		}
		str = ft_number_to_str(num, 'd', 10);
	}
	if (sp.u)
		str = ft_number_to_str(va_arg(args, unsigned int), 'd', 10);
	if (*str == '0' && flags.is_dot && !flags.pr_width)
	{
		free(str);
		return (ft_d_i_u("", &flags, &sp));
	}
	num = ft_d_i_u(str, &flags, &sp);
	free(str);
	return (num);
}

int	format_hexadecimal(va_list args, t_specifiers sp, t_flags flags)
{
	int					num;
	char				*str;

	num = va_arg(args, unsigned int);
	if (sp.x)
		str = ft_number_to_str(num, 'x', 16);
	if (sp.xcap)
		str = ft_number_to_str(num, 'X', 16);
	if (*str == '0' && flags.is_dot && !flags.pr_width)
	{
		free(str);
		return (ft_hex("", &flags, &sp));
	}
	num = ft_hex(str, &flags, &sp);
	free(str);
	return (num);
}

int	format_p(va_list args, t_specifiers sp, t_flags flags)
{
	int					num;
	unsigned long long	p_null;
	char				*str;

	p_null = va_arg(args, unsigned long long);
	if (!p_null)
		return (ft_c_s_p("(nil)", &flags, &sp));
	flags.is_hash = 1;
	str = ft_number_to_str_l(p_null, 'x', 16);
	if (*str == '0' && flags.is_dot && !flags.pr_width)
	{
		free(str);
		return (ft_hex("", &flags, &sp));
	}
	num = ft_hex(str, &flags, &sp);
	free(str);
	return (num);
}
