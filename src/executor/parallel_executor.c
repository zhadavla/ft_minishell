/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallel_executor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:17:49 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/01 14:17:50 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	do_fork(t_pipex *pipex, t_cmd *node_cmd, char **env)
{
	int	pid;
	int	dup_check;
	int	x;

	pid = fork();
	dup_check = 1;
	if (pid == 0)
	{
		dup_check = ft_dup2(node_cmd->infile_fd, node_cmd->outfile_fd);
		close_fd(pipex);
		ft_execute(node_cmd->cmd_full, env);
	}
	if (dup_check == -1)
	{
		write(2, "dup2 error\n", 11);
		exit(EXIT_FAILURE);
	}
}

void	parallel_executor(t_pipex pipex, t_cmd **cmd_node, char **env)
{
	execute_command(&pipex, *cmd_node, env);
	if (pipex.cmd_count > 1)
		free(pipex.fd_pipes);
}

void	execute_command(t_pipex *pipex, t_cmd *node_cmd, char **env)
{
	int	i;
	int	status;

	while (node_cmd)
	{
		do_fork(pipex, node_cmd, env);
		node_cmd = node_cmd->next;
	}
	close_fd(pipex);
	i = 0;
	while (++i < pipex->cmd_count)
		wait(&status);
}
