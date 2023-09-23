/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_cmds2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 19:59:05 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/23 20:00:05 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_exec_validation(t_minishell *minishell);

/**
 * later: don't forget to handle wrong command input
 * and return error message: "command not found"
 * */
void	validate_commands(t_minishell *minishell)
{
	t_token	*head;

	head = minishell->token;
	while (head)
	{
		if (head->type == WORD && ft_exec_validation(minishell) == TRUE)
			head->type = COMMAND;
		else if (head->type == ENV_VARIBLE || (head->type == WHITE_SPACE
				&& head->quote != QUOTE0))
			head->type = WORD;
		head = head->next;
		minishell->token = head;
	}
}

void	validate_filename(t_token **token)
{
	t_token	*head;

	head = *token;
	while (head)
	{
		if (head->next && (head->next->type == WORD
				|| head->next->type == COMMAND))
		{
			if (head->type == REDIR_APPEND)
				head->next->type = OUTFILE_AP;
			else if (head->type == REDIR_OUT)
				head->next->type = OUTFILE;
			else if (head->type == REDIR_IN)
				head->next->type = INFILE;
		}
		head = head->next;
	}
}

void	validate_commands_two(t_token **token)
{
	t_token	*head;

	head = *token;
	while (head)
	{
		if (head->next && head->type == COMMAND && head->next->type == COMMAND)
			head->next->type = WORD;
		head = head->next;
	}
}
