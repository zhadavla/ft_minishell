/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenate2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 20:53:28 by vzhadan           #+#    #+#             */
/*   Updated: 2023/08/17 19:10:06 by vzhadan          ###   ########.fr       */
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
