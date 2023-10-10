/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_file_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 20:01:54 by vzhadan           #+#    #+#             */
/*   Updated: 2023/08/25 20:29:15 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	executor(t_minishell *minishell)
{
	t_pipex	pipex;

	if (open_files(&minishell->cmd_node))
	{
		fprintf(stderr, C_RED "No such file or directory" C_RESET);
		return (1);
	}
	if (is_heredoc(minishell->cmd_node))
		return (sequential_executor(minishell));
	else
	{
		pipex = update_pipe_fds(&minishell->cmd_node);
		minishell->pipex = &pipex;
		return (parallel_executor(minishell));
	}
}
