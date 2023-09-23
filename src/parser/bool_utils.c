/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:27:05 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/23 20:05:45 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_pipe(t_token *token)
{
	return (token->type == PIPE);
}

int	is_redirection_in(t_token *token)
{
	return (token->type == REDIR_IN);
}

int	is_redirection_out(t_token *token)
{
	return (token->type == REDIR_OUT || token->type == REDIR_APPEND);
}

int	is_in_quotes(t_token *head)
{
	return ((head->quote == IN_QUOTE1 && head->next->quote == IN_QUOTE1)
		|| (head->quote == IN_QUOTE2 && head->next->quote == IN_QUOTE2));
}

int	is_quote(t_token *head)
{
	return (head->type == SINGLE_QUOTE || head->type == DOUBLE_QUOTE);
}
