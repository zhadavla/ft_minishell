/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 20:51:20 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/18 15:43:17 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_quote_error(t_token **token)
{
	if (((*token)->type == DOUBLE_QUOTE && (*token)->next->type == DOUBLE_QUOTE)
	|| ((*token)->type == SINGLE_QUOTE && (*token)->next->type == SINGLE_QUOTE))
		return (0);
	
}