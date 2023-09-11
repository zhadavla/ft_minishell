/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:34:27 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/11 19:38:48 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_putstr_fd(char *s, int fd);

void	error_heredoc(t_token **head, int error_type)
{
	if (error_type == 1)
	{
		free_tokens(*head);
		ft_putstr_fd("Heredoc has to be followed by a command\n",
			2);
		exit(SYNTAX_ERROR_NL);
	}
	if (error_type == 2)
	{
		free_tokens(*head);
		ft_putstr_fd("Delimeter has to be specified\n", 2);
		exit(SYNTAX_ERROR_NL);
	}
}

void	validate_heredoc(t_token **token)
{
	t_token	*head;
	t_token	*prev;

	head = *token;
	while (head)
	{
		if (head->type == HEREDOC)
		{
			if (head->next && head->next->type == WORD)
			{
				head->next->type = DELIM_H;
				if (!(head->next->next) || head->next->next->type != COMMAND)
					error_heredoc(&head, 1);
			}
			else
				error_heredoc(&head, 2);
		}
		head = head->next;
	}
}

int	is_heredoc(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->is_heredoc)
			return (TRUE);
		cmd = cmd->next;
	}
	return (FALSE);
}
