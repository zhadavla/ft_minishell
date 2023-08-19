/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenate2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 20:53:28 by vzhadan           #+#    #+#             */
/*   Updated: 2023/08/19 17:55:06 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Removing nodes with whitespaces
*/
void remove_whitespaces(t_token **token)
{
	t_token *tmp;
	t_token *prev;

	tmp = *token;
	prev = NULL;
	while (tmp)
	{
		if (tmp->type == WHITE_SPACE)
		{
			if (prev)
			{
				prev->next = tmp->next;
				free(tmp->text);
				free(tmp);
				tmp = prev->next;
			}
			else
			{
				*token = tmp->next;
				free(tmp->text);
				free(tmp);
				tmp = *token;
			}
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}	
}

void concate_leftover_strings(t_token **token)
{
	t_token *head;
	t_token *prev;
	
	head = *token;
	while (head)
	{
		if (head->type == WORD)
		{
			while (head->next && (head->next->type == WORD || head->next->type == ENV_VARIBLE))
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

void remove_quotes(t_token **token)
{
	t_token *head;
	t_token *prev;

	if ((*token) && ((*token)->type == SINGLE_QUOTE || (*token)->type == DOUBLE_QUOTE) 
		&& (*token)->quote == QUOTE0)
	{
		prev = *token;
		*token = (*token)->next;
		free_token(prev);
	}
	head = *token;
	while (head)
	{
		if (head->next && (head->next->type == SINGLE_QUOTE || head->next->type == DOUBLE_QUOTE) && head->next->quote == QUOTE0)
		{
			prev = head->next;
			head->next = head->next->next;
			free_token(prev);
		}
		head = head->next;
	}
}