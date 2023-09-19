/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_to_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:26:03 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/19 18:45:56 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	t_cmd_add(t_cmd **head, t_cmd *new)
{
	t_cmd	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

/**
 * Creates a new node of t_cmd
 * with the neccessary data for execution of the process
 *
 */
t_cmd	*new_cmd(t_token *till_pipe)
{
	t_cmd	*node_cmd;

	init_cmd_node(&node_cmd);
	if (till_pipe->type == BUILTIN)
		node_cmd->is_builtin = TRUE;
	handle_heredoc(&till_pipe, &node_cmd);
	handle_in_out_files(&till_pipe, &node_cmd);
	command_to_words(&till_pipe);
	create_full_command(&till_pipe, &node_cmd);
	return (node_cmd);
}

/**
 * Removes the node with redirections from the till_pipe list
 */
void	remove_redirections(t_token **till_pipe)
{
	t_token	*head;
	t_token	*prev;

	head = *till_pipe;
	prev = NULL;
	while (head)
	{
		if ((is_redirection_in(head) || is_redirection_out(head)))
		{
			prev = head;
			head = head->next;
			remove_node(till_pipe, prev);
		}
		head = head->next;
	}
}

/**
 * Populates the node of t_cmd
 * with the neccessary data for execution of the process
 * creates list of tokens before the pipe, named till_pipe
 */
t_cmd	*split_to_pipes(t_token **token)
{
	t_token	*head;
	t_token	*till_pipe;
	t_cmd	*cmd_head;
	t_cmd	*tmp_cmd;
 
	head = *token;
	till_pipe = NULL;
	cmd_head = NULL;
	while (head)
	{
		if (head->type == PIPE)
		{
			tmp_cmd = new_cmd(till_pipe);
			t_cmd_add(&cmd_head, tmp_cmd);
			till_pipe = NULL;
		}
		else
			t_add(&till_pipe, new_token(ft_strdup(head->text), head->len,
					head->type, head->quote));
		head = head->next;
	}
	tmp_cmd = new_cmd(till_pipe);
	t_cmd_add(&cmd_head, tmp_cmd);
	till_pipe = NULL;
	return (cmd_head);
}
