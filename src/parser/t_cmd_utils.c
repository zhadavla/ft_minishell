/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 20:50:31 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/15 19:45:39 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_cmd_nodes(t_cmd **head)
{
	t_cmd	*tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free_cmd_node(tmp);
		free(tmp);
	}
}

void	free_cmd_node(t_cmd *cmd_node)
{
	int	i;

	i = 0;
	free(cmd_node->delim);
	free(cmd_node->infile_name);
	free(cmd_node->outfile_name);
	while (cmd_node->cmd_full[i] != NULL)
		free(cmd_node->cmd_full[i++]);
	i = 0;
	while (cmd_node->infile_names[i] != NULL)
		free(cmd_node->infile_names[i++]);
	i = 0;
	while (cmd_node->outfile_names[i] != NULL)
		free(cmd_node->outfile_names[i++]);
	free(cmd_node->infile_names);
	free(cmd_node->outfile_names);
	free(cmd_node->cmd_full);
}
