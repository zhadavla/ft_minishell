/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenate1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:45:46 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/11 18:55:02 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	concatenate_minus(t_token **token);

/**
 * Merge heredoc and redirection_append into one token
 */
void	merge_redirections_heredoc(t_token **token)
{
	t_token	*head;
	t_token	*tmp;
	t_token	*prev;

	head = *token;
	while (head)
	{
		if ((head->type == REDIR_APPEND && head->next->type == REDIR_OUT)
			|| (head->type == HEREDOC && head->next->type == REDIR_IN))
		{
			head->text = ft_strjoin(head->text, head->next->text);
			head->len += head->next->len;
			prev = head->next;
			head->next = head->next->next;
			free_token(prev);
		}
		head = head->next;
	}
}

/**
 * Merge env variables with words in quotes
 * also update len of token
 * it should also free the old token
 *
 */
void	concate_quotes(t_token **token)
{
	t_token	*head;
	t_token	*tmp;
	t_token	*prev;

	head = *token;
	while (head)
	{
		if (is_in_quotes(head))
		{
			tmp = head;
			while (tmp->next && tmp->next->quote == head->quote)
			{
				head->text = ft_strjoin(head->text, tmp->next->text);
				head->len += tmp->next->len;
				prev = tmp;
				tmp = tmp->next;
				if (prev != head)
					free_token(prev);
			}
			head->next = tmp->next;
			free_token(tmp);
			head->type = WORD;
		}
		head = head->next;
	}
}

void	concatenate_minus(t_token **token)
{
	t_token	*head;
	t_token	*tmp;
	t_token	*prev;

	head = *token;
	while (head)
	{
		if (head->next && head->text[0] == '-')
		{
			head->text = ft_strjoin(head->text, head->next->text);
			head->len += head->next->len;
			prev = head->next;
			head->next = head->next->next;
			free_token(prev);
		}
		head = head->next;
	}
}
