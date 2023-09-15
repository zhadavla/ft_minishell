/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_full_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:03:39 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/15 19:01:25 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	redirections_switch(t_token *token, t_cmd **cmd_node);
static int	count_parameters(t_token *token);

/**
 * ????
 */
void	command_to_words(t_token **till_pipe)
{
	t_token	*head;

	head = *till_pipe;
	while (head)
	{
		if (head->type == COMMAND)
			break ;
		head = head->next;
	}
	if (head)
		head = head->next;
	while (head)
	{
		if (head->type == COMMAND)
			head->type = WORD;
		head = head->next;
	}
}

/**
 * ???
 */
static int	count_parameters(t_token *token)
{
	int	count;
	int	is_command;

	count = 0;
	is_command = FALSE;
	while (token)
	{
		if (token->type == COMMAND)
		{
			is_command = TRUE;
			count++;
		}
		else if (is_command && (token->type == PIPE || token->type == REDIR_OUT
				|| token->type == REDIR_IN || token->type == REDIR_APPEND
				|| token->type == HEREDOC))
		{
			is_command = FALSE;
			return (count);
		}
		else if (is_command && token->type == WORD)
			count++;
		token = token->next;
	}
	return (count);
}

/**
 * Creates **full_command array in cmd_node
 */
void	create_full_command(t_token **token, t_cmd **cmd_node)
{
	char	**full_command;
	int		i;
	int		is_command;
	t_token	*prev;

	full_command = malloc(sizeof(char *) * (count_parameters(*token) + 1));
	i = -1;
	is_command = FALSE;
	while (*token)
	{
		if ((*token)->type == COMMAND)
		{
			is_command = TRUE;
			full_command[++i] = ft_strdup((*token)->text);
		}
		else if (is_command && ((*token)->type == WORD
				|| (*token)->type == ENV_VARIBLE))
			full_command[++i] = ft_strdup((*token)->text);
		prev = *token;
		*token = (*token)->next;
		free_token(prev);
	}
	full_command[++i] = NULL;
	(*cmd_node)->cmd_full = full_command;
	(*cmd_node)->next = NULL;
}

void	init_cmd_node(t_cmd **cmd_node)
{
	*cmd_node = malloc(sizeof(t_cmd));
	(*cmd_node)->is_builtin = FALSE;
	(*cmd_node)->is_before_heredoc = FALSE;
	(*cmd_node)->is_after_heredoc = FALSE;
	(*cmd_node)->is_heredoc = FALSE;
	(*cmd_node)->is_append = FALSE;
	(*cmd_node)->delim = NULL;
	(*cmd_node)->infile_name = NULL;
	(*cmd_node)->outfile_name = NULL;
	(*cmd_node)->infile_names = NULL;
	(*cmd_node)->outfile_names = NULL;
	(*cmd_node)->infile_fd = 0;
	(*cmd_node)->outfile_fd = 1;
	(*cmd_node)->cmd_full = NULL;
	(*cmd_node)->env = NULL;
	(*cmd_node)->cmd_path = NULL;
	(*cmd_node)->is_last = FALSE;
	(*cmd_node)->is_first = FALSE;
	(*cmd_node)->next = NULL;
}
