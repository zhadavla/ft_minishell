/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallel_exec2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 18:45:55 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/23 18:47:26 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		do_fork(t_minishell *minishell, t_cmd *node_cmd);
int			is_builtin_without_output(t_cmd *node_cmd);
int			execute_builtin_without_output(t_minishell *minishell);

static int	parent_wait(t_minishell *minishell, int cmd_count)
{
	int	i;
	int	exit_status;
	int	status;

	exit_status = 0;
	i = -1;
	if (!is_builtin_without_output(minishell->cmd_node))
	{
		while (++i < cmd_count)
		{
			wait(&status);
			if (WIFEXITED(status) == 1)
				exit_status = WEXITSTATUS(status);
		}
	}
	return (exit_status);
}

int	execute_command(t_minishell *minishell)
{
	int		exit_status;
	t_cmd	*node_cmd;
	t_pipex	*pipex;

	exit_status = 0;
	node_cmd = minishell->cmd_node;
	pipex = minishell->pipex;
	while (node_cmd)
	{
		if (is_builtin_without_output(node_cmd))
			exit_status = execute_builtin_without_output(minishell);
		else
			do_fork(minishell, node_cmd);
		node_cmd = node_cmd->next;
	}
	close_fd(pipex);
	exit_status = parent_wait(minishell, pipex->cmd_count);
	signal(SIGINT, ft_newline);
	return (exit_status);
}
