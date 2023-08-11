/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 20:18:04 by vzhadan           #+#    #+#             */
/*   Updated: 2023/03/11 16:38:02 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_fill_flags(char *str, t_flags *flags)
{
	const char	str_flags[] = "csdiuxpX%";

	while (!ft_strchr(str_flags, *str))
	{
		ft_switch_for_flags(*str, flags);
		if (*str == '0' && !(flags->width) && !(flags->pr_width))
			flags->is_zero = 1;
		if (ft_isdigit(*str) && !(flags->is_dot))
			ft_fill_width(*str, flags);
		else if (ft_isdigit(*str) && flags->is_dot)
			ft_fill_pr_width(*str, flags);
		str++;
	}
	return (str);
}

int	ft_format(va_list args, t_specifiers sp, t_flags flags)
{
	char				*str;
	int					num;

	if (sp.percent)
		return (write(1, "%", 1));
	else if (sp.c)
		return (format_c(args, sp, flags));
	else if (sp.d || sp.i || sp.u)
		return (format_int(args, sp, flags));
	else if (sp.s)
	{
		str = va_arg(args, char *);
		if (!str)
			return (ft_c_s_p("(null)", &flags, &sp));
		num = ft_c_s_p(str, &flags, &sp);
		return (num);
	}
	else if (sp.p)
		return (format_p(args, sp, flags));
	else if (sp.x || sp.xcap)
		return (format_hexadecimal(args, sp, flags));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	t_flags			flags;
	t_specifiers	sp;
	va_list			ptr;
	size_t			printed;
	char			*tmp_ptr;

	printed = 0;
	tmp_ptr = (char *)str;
	va_start(ptr, str);
	ft_init(&flags, &sp);
	while (*(tmp_ptr))
	{
		if (*tmp_ptr == '%')
		{
			ft_init(&flags, &sp);
			tmp_ptr = ft_fill_flags(tmp_ptr + 1, &flags);
			ft_switch_for_sp(*tmp_ptr, &sp);
			printed += ft_format(ptr, sp, flags);
		}
		else
			printed += write(1, &(*tmp_ptr), 1);
		tmp_ptr ++;
	}
	return (printed);
}
