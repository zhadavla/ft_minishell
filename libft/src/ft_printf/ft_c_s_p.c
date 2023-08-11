/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_c_s_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 20:18:04 by vzhadan           #+#    #+#             */
/*   Updated: 2023/08/05 16:04:33 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_c_s_p_width(char *str, t_flags *flags, int len)
{
	int	printed;

	printed = 0;
	if (flags->is_dash)
	{
		printed += ft_putstr_utils(str, len);
		printed += ft_putspace(flags->width - len);
	}
	if (!flags->is_dash)
	{
		printed += ft_putspace(flags->width - len);
		printed += ft_putstr_utils(str, len);
	}
	return (printed);
}

int	ft_c_s_p(char *str, t_flags *flags, t_specifiers *sp)
{
	int	len;
	int	printed;

	if (!ft_strncmp(str, "(null)", 6) && flags->is_dot && flags->pr_width < 6)
		return (0);
	printed = 0;
	len = ft_strlen(str);
	if (sp->s && flags->is_dot && flags->pr_width < len)
		len = flags->pr_width;
	if (sp->c && *str == '\0')
		len = 1;
	if (flags->width)
		printed += ft_c_s_p_width(str, flags, len);
	if (!flags->width)
		printed += ft_putstr_utils(str, len);
	return (printed);
}
