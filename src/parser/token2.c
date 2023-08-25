/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 20:14:50 by vzhadan           #+#    #+#             */
/*   Updated: 2023/08/25 20:47:06 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// change quote status if quote is opened or closed
t_quote	update_q_s(char c, enum e_quote quote)
{
	if ((c == '\'' && quote == IN_QUOTE1) || (c == '\"' && quote == IN_QUOTE2))
		return (QUOTE0);
	else if (c == '\'' && quote == QUOTE0)
		return (IN_QUOTE1);
	else if (c == '\"' && quote == QUOTE0)
		return (IN_QUOTE2);
	else if (c == '\'' && quote == IN_QUOTE2)
		return (IN_QUOTE2);
	else if (c == '\"' && quote == IN_QUOTE1)
		return (IN_QUOTE1);
	return (QUOTE0);
}

/**
 * Returns token type, depending on the characters
*/
t_token_type	update_token_type(char c, char d)
{
	if (c == '|')
		return (PIPE);
	if (c == '<' && d != '<')
		return (REDIR_IN);
	if (c == '>' && d != '>')
		return (REDIR_OUT);
	if (c == '>' && d == '>')
		return (REDIR_APPEND);
	if (c == '<' && d == '<')
		return (HEREDOC);
	if (c == '\'')
		return (SINGLE_QUOTE);
	if (c == '\"')
		return (DOUBLE_QUOTE);
	if (c == '$' || c == '~')
		return (ENV_VARIBLE);
	if (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r')
		return (WHITE_SPACE);
	return (WORD);
}

t_token	*new_token(char *text, size_t len, t_token_type type,
		t_quote quote)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->text = text;
	new->len = len;
	new->type = type;
	new->quote = quote;
	new->next = NULL;
	return (new);
}

void	free_token(t_token *token)
{
	free(token->text);
	free(token);
}

void	free_tokens(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free_token(tmp);
	}
}
