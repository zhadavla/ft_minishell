/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:04:20 by vzhadan           #+#    #+#             */
/*   Updated: 2023/10/10 18:19:34 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Removes the node from the list of tokens
 */
void	remove_node(t_token **token, t_token *node)
{
	t_token	*head;
	t_token	*prev;

	head = *token;
	prev = NULL;
	while (head)
	{
		if (head == node)
		{
			if (prev)
				prev->next = head->next;
			else
				*token = head->next;
			free_token(head);
			return ;
		}
		prev = head;
		head = head->next;
	}
}

void	remove_node_cmd(t_cmd **cmd_node, t_cmd *node)
{
	t_cmd	*head;
	t_cmd	*prev;

	head = *cmd_node;
	prev = NULL;
	while (head)
	{
		if (head == node)
		{
			if (prev)
				prev->next = head->next;
			else
				*cmd_node = head->next;
			free_cmd_node(head);
			free(head);
			return ;
		}
		prev = head;
		head = head->next;
	}
}
