/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 20:51:20 by vzhadan           #+#    #+#             */
/*   Updated: 2023/10/10 18:41:27 by vzhadan          ###   ########.fr       */
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
