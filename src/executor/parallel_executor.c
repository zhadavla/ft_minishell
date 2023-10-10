/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallel_executor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:17:49 by vzhadan           #+#    #+#             */
/*   Updated: 2023/10/10 17:39:06 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	my_child(int sig)
{
	if (sig == SIGINT)
		exit(130);
}

void	do_fork(t_minishell *minishell, t_cmd *node_cmd)
{
	int		pid;
	t_pipex	*pipex;
	char	**env;

	pipex = minishell->pipex;
	env = minishell->env;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, my_child);
		if (node_cmd->exit_status != 0)
			exit(127);
		if (ft_dup2(node_cmd->infile_fd, node_cmd->outfile_fd) == -1)
		{
			write(2, "dup2 error\n", 11);
			exit(EXIT_FAILURE);
		}
		close_fd(pipex);
		if (node_cmd->is_builtin)
			ft_execute_builtin(minishell, node_cmd, 0);
		else if (!ft_execute(node_cmd->cmd_full, env))
			exit(42);
	}
	signal(SIGINT, SIG_IGN);
}

int	parallel_executor(t_minishell *minishell)
{
	int	exit;

	exit = execute_command(minishell);
	if (minishell->pipex->cmd_count > 1)
		free(minishell->pipex->fd_pipes);
	return (exit);
}

int	is_builtin_without_output(t_cmd *node_cmd)
{
	char	*cmd;

	if (node_cmd->is_builtin)
	{
		cmd = node_cmd->cmd_full[0];
		return (!ft_strncmp(cmd, "cd", 3) || !ft_strncmp(cmd, "export", 7)
			|| !ft_strncmp(cmd, "unset", 6) || !ft_strncmp(cmd, "exit", 5));
	}
	return (FALSE);
}

int	execute_builtin_without_output(t_minishell *minishell)
{
	t_cmd	*cmd_node;
	
	if (minishell->is_builtin_wo_command)
	{
		fprintf(stderr, "??????????\n");
		return (0);
	}
	cmd_node = minishell->cmd_node;
	if (!ft_strncmp(cmd_node->cmd_full[0], "cd", 3))
		return (ft_cd(minishell));
	if (!ft_strncmp(cmd_node->cmd_full[0], "export", 7))
		return (ft_export(minishell));
	else if (!ft_strncmp(cmd_node->cmd_full[0], "unset", 6))
		return (ft_unset(minishell));
	else if (!ft_strncmp(cmd_node->cmd_full[0], "exit", 5))
		ft_exit(minishell);
	return (0);
}
