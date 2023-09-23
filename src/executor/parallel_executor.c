/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallel_executor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:17:49 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/23 18:04:59 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	my_child(int sig)
{
	if (sig == SIGINT)
	{
		// fprintf(stderr, C_RED "child exit\n" C_RESET);
		exit(130);
	}
}

static void	do_fork(t_minishell *minishell, t_cmd *node_cmd)
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
			ft_execute_builtin(minishell);
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

int	execute_command(t_minishell *minishell)
{
	int		i;
	int		status;
	int		exit_status;
	t_cmd	*node_cmd;
	t_pipex	*pipex;

	node_cmd = minishell->cmd_node;
	pipex = minishell->pipex;
	while (node_cmd)
	{
		if (is_builtin_without_output(node_cmd))
		{
			// fprintf(stderr, C_GREEN "this is fine\n" C_RESET);
			exit_status = execute_builtin_without_output(minishell);
		}
		else
			do_fork(minishell, node_cmd);
		node_cmd = node_cmd->next;
	}
	i = -1;
	close_fd(pipex);
	if (!is_builtin_without_output(minishell->cmd_node))
	{
		// fprintf(stderr, C_GREEN "it shouldn't be printed\n" C_RESET);
		while (++i < pipex->cmd_count)
		{
			wait(&status);
			if (WIFEXITED(status) == 1)
				exit_status = WEXITSTATUS(status);
		}
	}
	signal(SIGINT, ft_newline);
	return (exit_status);
}
