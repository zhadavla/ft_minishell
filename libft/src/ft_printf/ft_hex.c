/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 20:18:04 by vzhadan           #+#    #+#             */
/*   Updated: 2023/08/05 16:04:33 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putsigns_hex(t_flags *flags, t_specifiers *sp)
{
	if ((sp->x || sp->p) && flags->is_hash)
	{
		ft_putstr_utils("0", 1);
		ft_putstr_utils("x", 1);
		return (2);
	}
	if ((sp->xcap) && flags->is_hash)
	{
		ft_putstr_utils("0", 1);
		ft_putstr_utils("X", 1);
		return (2);
	}
	return (0);
}

int	ft_no_width_hex(char *str, t_flags *flags, t_specifiers *sp, int len)
{
	int	printed;

	printed = 0;
	if (flags->is_hash)
		printed += ft_putsigns_hex(flags, sp);
	if (flags->is_dot && flags->pr_width > len)
		printed += ft_putzero(flags->pr_width - len);
	printed += ft_putstr_utils(str, len);
	return (printed);
}

int	ft_width_dash_hex(char *str, t_flags *flags, t_specifiers *sp, int len)
{
	int	printed;

	printed = 0;
	if (flags->is_hash)
	{
		printed += ft_putsigns_hex(flags, sp);
		len += 2;
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

int	ft_width_no_dash_hex(char *str, t_flags *flags, t_specifiers *sp, int len)
{
	int	printed;

	printed = 0;
	if (flags->is_hash)
		len += 2;
	len = flags->width - len;
	if (!flags->is_zero)
	{
		if (flags->pr_width && flags->pr_width > (int)ft_strlen(str))
			printed += ft_putspace(len - (flags->pr_width - ft_strlen(str)));
		else
			printed += ft_putspace(len);
		if (flags->is_hash)
			printed += ft_putsigns_hex(flags, sp);
		if (flags->is_dot && flags->pr_width > (int)ft_strlen(str))
			printed += ft_putzero(flags->pr_width - ft_strlen(str));
	}
	if (flags->is_zero)
	{
		if (flags->is_hash)
			printed += ft_putsigns_hex(flags, sp);
		printed += ft_putzero(len);
	}
	printed += ft_putstr_utils(str, ft_strlen(str));
	return (printed);
}

int	ft_hex(char *str, t_flags *flags, t_specifiers *sp)
{
	int	len;
	int	printed;

	printed = 0;
	len = ft_strlen(str);
	if (*str == '0' || !*str)
		flags->is_hash = 0;
	if (flags->is_dot)
		flags->is_zero = 0;
	if (flags->is_dot && flags->pr_width >= flags->width)
		flags->width = 0;
	if (!flags->width)
		printed += ft_no_width_hex(str, flags, sp, len);
	if (flags->width && flags->width > flags->pr_width)
	{
		if (flags->is_dash)
			printed += ft_width_dash_hex(str, flags, sp, len);
		if (!flags->is_dash)
			printed += ft_width_no_dash_hex(str, flags, sp, len);
	}
	return (printed);
}
