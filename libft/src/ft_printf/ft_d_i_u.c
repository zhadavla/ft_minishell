/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_d_i_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 20:18:04 by vzhadan           #+#    #+#             */
/*   Updated: 2023/08/05 16:04:33 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_no_width(char *str, t_flags *flags, t_specifiers *sp, int len)
{
	int	printed;

	printed = 0;
	if (flags->is_negative || flags->is_plus || flags->is_space)
		printed += ft_putsigns(flags, sp);
	if (flags->is_dot && flags->pr_width > len)
		printed += ft_putzero(flags->pr_width - len);
	printed += ft_putstr_utils(str, len);
	return (printed);
}

int	ft_width_dash(char *str, t_flags *flags, t_specifiers *sp, int len)
{
	int	printed;

	printed = 0;
	if (flags->is_negative || flags->is_plus || flags->is_space)
	{
		printed += ft_putsigns(flags, sp);
		len += 1;
	}
	len = flags->width - len;
	if (flags->is_dot && flags->pr_width > (int)ft_strlen(str))
		printed += ft_putzero(flags->pr_width - ft_strlen(str));
	printed += ft_putstr_utils(str, ft_strlen(str));
	if (flags->pr_width && flags->pr_width > (int)ft_strlen(str))
		printed += ft_putspace(len - (flags->pr_width - ft_strlen(str)));
	else
		printed += ft_putspace(len);
	return (printed);
}

int	ft_width_no_dash(char *str, t_flags *flags, t_specifiers *sp, int len)
{
	int	printed;

	printed = 0;
	if (flags->is_negative || flags->is_plus || flags->is_space)
		len += 1;
	len = flags->width - len;
	if (!flags->is_zero)
	{
		if (flags->pr_width && flags->pr_width > (int)ft_strlen(str))
			printed += ft_putspace(len - (flags->pr_width - ft_strlen(str)));
		else
			printed += ft_putspace(len);
		if (flags->is_negative || flags->is_plus || flags->is_space)
			printed += ft_putsigns(flags, sp);
		if (flags->is_dot && flags->pr_width > (int)ft_strlen(str))
			printed += ft_putzero(flags->pr_width - ft_strlen(str));
	}
	if (flags->is_zero)
	{
		if (flags->is_negative || flags->is_plus || flags->is_space)
			printed += ft_putsigns(flags, sp);
		printed += ft_putzero(len);
	}
	printed += ft_putstr_utils(str, ft_strlen(str));
	return (printed);
}

int	ft_d_i_u(char *str, t_flags *flags, t_specifiers *sp)
{
	int	len;
	int	printed;

	printed = 0;
	len = ft_strlen(str);
	if (flags->is_dot)
		flags->is_zero = 0;
	if (flags->is_dot && flags->pr_width >= flags->width)
		flags->width = 0;
	if (!flags->width)
		printed += ft_no_width(str, flags, sp, len);
	if (flags->width && flags->width > flags->pr_width)
	{
		if (flags->is_dash)
			printed += ft_width_dash(str, flags, sp, len);
		if (!flags->is_dash)
			printed += ft_width_no_dash(str, flags, sp, len);
	}
	return (printed);
}
