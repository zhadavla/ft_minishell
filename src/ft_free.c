/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:04:20 by vzhadan           #+#    #+#             */
/*   Updated: 2023/08/21 18:04:29 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Removes the node from the list of tokens
*/
void remove_node(t_token **token, t_token *node)
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