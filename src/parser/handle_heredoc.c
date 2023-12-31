/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:50:19 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/20 14:00:38 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_front_t_cmd(t_cmd **cmd_node, t_cmd *new)
{
	t_cmd	*tmp;

	if (!*cmd_node)
	{
		*cmd_node = new;
		return ;
	}
	tmp = *cmd_node;
	*cmd_node = new;
	(*cmd_node)->next = tmp;
}

t_cmd	*copy_t_cmd(t_cmd *node)
{
	t_cmd	*new;
	int		i;

	init_cmd_node(&new);
	new->infile_name = ft_strdup(node->infile_name);
	new->outfile_name = ft_strdup(node->outfile_name);
	i = -1;
	while (node->infile_names[++i] != NULL)
		new->infile_names[i] = ft_strdup(node->infile_names[i]);
	i = -1;
	while (node->outfile_names[++i] != NULL)
		new->outfile_names[i] = ft_strdup(node->outfile_names[i]);
	new->delim = ft_strdup(node->delim);
	new->is_heredoc = node->is_heredoc;
	new->next = NULL;
	return (new);
}

/**
 * Move heredoc node to the first place
 * Marks nodes after and before heredoc.
 */
void	move_to_first_place_heredoc(t_cmd **cmd_head)
{
	t_cmd	*head;
	t_cmd	*prev;

	head = *cmd_head;
	prev = NULL;
	while (head)
	{
		if (head->is_heredoc)
		{
			if (head->next)
				head->next->is_after_heredoc = TRUE;
			prev->is_before_heredoc = TRUE;
			prev->next = head->next;
			head->next = *cmd_head;
			*cmd_head = head;
			break ;
		}
		prev = head;
		head = head->next;
	}
}

/**
 * Find heredoc node,
	remove node with heredoc and delimeter from till_pipe list.
 */
void	handle_heredoc(t_token **till_pipe, t_cmd **cmd_node)
{
	t_token	*head;
	t_token	*prev;

	head = *till_pipe;
	prev = NULL;
	while (head)
	{
		if (head->type == HEREDOC && head->next && head->next->type == DELIM_H)
		{
			(*cmd_node)->is_heredoc = TRUE;
			(*cmd_node)->delim = ft_strdup(head->next->text);
			prev = head;
			head = head->next;
			remove_node(till_pipe, prev);
			prev = head;
			head = head->next;
			remove_node(till_pipe, prev);
		}
		head = head->next;
	}
}
