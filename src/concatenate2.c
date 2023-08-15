/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenate2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 20:53:28 by vzhadan           #+#    #+#             */
/*   Updated: 2023/08/15 21:39:59 by vzhadan          ###   ########.fr       */
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

/**
 * Counting parameters of command
*/
size_t count_parameters(t_token *token)
{
	size_t count;

	count = 0;

	while (token)
	{
		if (token->type == COMMAND)
		{
			while (token)
			{
				printf("-----------------------------token->text = %s\n", token->text);
				if (token->next && (token->next->type == PIPE || token->next->type == REDIR_OUT
				|| token->next->type == REDIR_IN || token->next->type == REDIR_APPEND
				|| token->next->type == HEREDOC))
				{
					break;
				}
				count++;
				token = token->next;
			}
			break;
		}
		token = token->next;
	}
	printf("count = %zu\n", count + 1);
	return (count + 1);
}

/**
 * Creating char ** with all parameters of command
*/
char **create_full_command(t_token *token)
{
	char **full_command;
	size_t i;

	i = 0;
	full_command = (char **)malloc(sizeof(char *) * (count_parameters(token) + 1));
	while (token)
	{
		if (token->type == COMMAND)
		{
			while (token )
			{
				
				full_command[i] = ft_strdup(token->text);
				i++;
				if (token && (token->next->type == PIPE || token->next->type == REDIR_OUT
					|| token->next->type == REDIR_IN || token->next->type == REDIR_APPEND
					|| token->next->type == HEREDOC))
				{
					break;
				}
				token = token->next;
			}
			break;
		}		
		token = token->next;
	}
	full_command[i] = NULL;
	return (full_command);
}