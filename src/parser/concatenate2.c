/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenate2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 20:53:28 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/23 20:05:01 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	remove_whitespace(t_token **prev, t_token **tmp, t_token **token);
int			is_quote(t_token *head);

/**
 * Removeing one whitespace from the token,
 * because we don't need them anymore
 * also free up memory
 */
static void	remove_whitespace(t_token **prev, t_token **tmp, t_token **token)
{
	if (*prev)
	{
		(*prev)->next = (*tmp)->next;
		if ((*tmp)->text)
			free((*tmp)->text);
		if (*tmp)
			free(*tmp);
		(*tmp) = (*prev)->next;
	}
	else
	{
		*token = (*tmp)->next;
		if ((*tmp)->text)
			free((*tmp)->text);
		if (*tmp)
			free(*tmp);
		(*tmp) = *token;
	}
}

/**
 * Removing nodes with whitespaces
 */
void	remove_whitespaces(t_token **token)
{
	t_token	*tmp;
	t_token	*prev;

	tmp = *token;
	prev = NULL;
	while (tmp)
	{
		if (tmp->type == WHITE_SPACE)
			remove_whitespace(&prev, &tmp, token);
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
}

/**
 * Merge words to one token
 */
void	concate_leftover_strings(t_token **token)
{
	t_token	*head;
	t_token	*prev;

	head = *token;
	while (head)
	{
		if (head->type == WORD)
		{
			while (head->next && (head->next->type == WORD
					|| head->next->type == ENV_VARIBLE))
			{
				head->text = ft_strjoin(head->text, head->next->text);
				head->len += head->next->len;
				prev = head->next;
				head->next = head->next->next;
				free_token(prev);
			}
		}
		head = head->next;
	}
}

void	check_first_node(t_token **token, t_token **prev)
{
	if ((*token) && (is_quote(*token)) && (*token)->quote == QUOTE0)
	{
		*prev = *token;
		*token = (*token)->next;
		free_token(*prev);
	}
}

/**
 * Remove quotes from tokens,
 * because we don't need them anymore
 */
void	remove_quotes(t_token **token)
{
	t_token	*head;
	t_token	*prev;

	check_first_node(token, &prev);
	head = *token;
	while (head)
	{
		if (head->next && (is_quote(head->next)) && head->next->quote == QUOTE0)
		{
			if (head->next->next && is_quote(head->next->next)
				&& head->next->next->quote == QUOTE0)
			{
				prev = head->next;
				head->next = head->next->next;
				free_token(prev);
			}
			prev = head->next;
			head->next = head->next->next;
			free_token(prev);
		}
		head = head->next;
	}
}
