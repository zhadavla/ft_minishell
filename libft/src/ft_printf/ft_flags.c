/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 20:18:04 by vzhadan           #+#    #+#             */
/*   Updated: 2023/08/05 16:04:33 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_switch_for_flags(char c, t_flags *flags)
{
	if (c == '.')
		flags->is_dot = 1;
	else if (c == ' ')
		flags->is_space = 1;
	else if (c == '#')
		flags->is_hash = 1;
	else if (c == '+')
		flags->is_plus = 1;
	else if (c == '-')
		flags->is_dash = 1;
}

void	ft_switch_for_sp(char c, t_specifiers *sp)
{
	if (c == 'c')
		sp->c = 1;
	else if (c == 'd')
		sp->d = 1;
	else if (c == 'i')
		sp->i = 1;
	else if (c == 's')
		sp->s = 1;
	else if (c == 'p')
		sp->p = 1;
	else if (c == '%')
		sp->percent = 1;
	else if (c == 'x')
		sp->x = 1;
	else if (c == 'X')
		sp->xcap = 1;
	else if (c == 'u')
		sp->u = 1;
}

void	ft_add_to_number(char c, int *prev_number)
{
	(*prev_number) = (*prev_number) * 10 + (c - '0');
}

void	ft_fill_pr_width(char c, t_flags *flags)
{
	ft_add_to_number(c, &(flags->pr_width));
}

void	ft_fill_width(char c, t_flags *flags)
{
	ft_add_to_number(c, &(flags->width));
}
