/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 20:51:20 by vzhadan           #+#    #+#             */
/*   Updated: 2023/08/15 20:51:34 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_unclosed_quotes(t_token **token)
{
	t_token	*head;

	head = *token;
	while (head->next)
		head = head->next;
	return (head->quote == IN_QUOTE1 || head->quote == IN_QUOTE2);
}
