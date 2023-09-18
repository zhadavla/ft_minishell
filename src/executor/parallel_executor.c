/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallel_executor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:17:49 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/18 14:21:22 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	do_fork(t_pipex *pipex, t_cmd *node_cmd, char **env,
		t_env **env_list)
{
	int	pid;
	int	dup_check;
	int	x;

	pid = fork();
	dup_check = 1;
	if (pid == 0)
	{
		fprintf(stderr, C_RED "child\n" C_RESET);
		dup_check = ft_dup2(node_cmd->infile_fd, node_cmd->outfile_fd);
		close_fd(pipex);
		if (node_cmd->is_builtin)
		{
			fprintf(stderr, C_YELLOW "builtin\n" C_RESET);
			ft_execute_builtin(node_cmd, env, env_list);
		}
		else
			ft_execute(node_cmd->cmd_full, env);
	}
	if (dup_check == -1)
	{
		write(2, "dup2 error\n", 11);
		exit(EXIT_FAILURE);
	}
}

void	parallel_executor(t_pipex pipex, t_cmd **cmd_node, char **env,
		t_env **env_list)
{
	execute_command(&pipex, *cmd_node, env, env_list);
	if (pipex.cmd_count > 1)
		free(pipex.fd_pipes);
}

void	execute_command(t_pipex *pipex, t_cmd *node_cmd, char **env,
		t_env **env_list)
{
	int	i;
	int	status;

	while (node_cmd)
	{
		do_fork(pipex, node_cmd, env, env_list);
		node_cmd = node_cmd->next;
	}
	close_fd(pipex);
	i = -1;
	while (++i < pipex->cmd_count)
		wait(&status);
}
