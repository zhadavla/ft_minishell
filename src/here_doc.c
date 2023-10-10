/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julienmoigno <julienmoigno@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:34:27 by vzhadan           #+#    #+#             */
/*   Updated: 2023/10/10 09:12:14 by julienmoign      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_putstr_fd(char *s, int fd);

void	error_heredoc(t_token **head, int error_type, t_minishell *minishell)
{
	if (error_type == 1)
	{
		free_tokens(*head);
		ft_putstr_fd("Heredoc has to be followed by a command\n",
			2);
	}
	if (error_type == 2)
	{
		free_tokens(*head);
		ft_putstr_fd("Delimeter has to be specified\n", 2);
	}
	minishell->exit_status = 2;
}

int	validate_heredoc(t_token **token, t_minishell *minishell)
{
	t_token	*head;

	head = *token;
	while (head)
	{
		if (head->type == HEREDOC)
		{
			if (head->next && head->next->type == WORD)
			{
				head->next->type = DELIM_H;
				if (!(head->next->next) || head->next->next->type != COMMAND)
				{
					error_heredoc(&head, 1, minishell);
					return (2);
				}
			}
			else
			{
				error_heredoc(&head, 2, minishell);
				return (2);
			}
		}
		head = head->next;
	}
	return (0);
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
