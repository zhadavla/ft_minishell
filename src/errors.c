/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julienmoigno <julienmoigno@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 20:51:20 by vzhadan           #+#    #+#             */
/*   Updated: 2023/10/10 09:00:32 by julienmoign      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_quote_error(t_token **token)
{
	if (((*token)->type == DOUBLE_QUOTE && (*token)->next->type == DOUBLE_QUOTE)
		|| ((*token)->type == SINGLE_QUOTE 
			&& (*token)->next->type == SINGLE_QUOTE))
		return (0);
	return (1);
}
