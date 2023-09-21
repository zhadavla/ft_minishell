/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallel_executor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:17:49 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/20 20:46:12 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	my_child(int sig)
{
	if (sig == SIGINT)
	{
		fprintf(stderr, C_RED "child exit\n" C_RESET);
		exit(130);
	}
}

static void	do_fork(t_minishell *minishell)
{
	int	pid;
	int	dup_check;
	int	x;
	t_cmd	*node_cmd = minishell->cmd_node;
	t_pipex	*pipex = minishell->pipex;
	char	**env = minishell->env;
	

	pid = fork();
	dup_check = 1;
	if (pid == 0)
	{
		signal(SIGINT, my_child);
		fprintf(stderr, C_RED "child\n" C_RESET);
		dup_check = ft_dup2(node_cmd->infile_fd, node_cmd->outfile_fd);
		if (node_cmd->exit_status != 0)
			exit(127);
		if (dup_check == -1)
		{
			write(2, "dup2 error\n", 11);
			exit(EXIT_FAILURE);
		}
		close_fd(pipex);
		if (node_cmd->is_builtin)
		{
			fprintf(stderr, C_YELLOW "builtin\n" C_RESET);
			ft_execute_builtin(minishell);
		}
		else if (!ft_execute(node_cmd->cmd_full, env))
			exit(42);
	}
	signal(SIGINT, SIG_IGN);
	fprintf(stderr, C_GREEN "after exit\n" C_RESET);
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
		return (!ft_strncmp(cmd, "cd", 3) || 
			!ft_strncmp(cmd, "export", 7)
			|| !ft_strncmp(cmd, "unset", 6) 
			|| !ft_strncmp(cmd, "exit", 5)
			|| !ft_strncmp(cmd, "env", 4));
	}
	return (FALSE);
}

void	execute_builtin_without_output(t_minishell *minishell)
{
	t_cmd	*cmd_node;

	cmd_node = minishell->cmd_node;
	if (!ft_strncmp(cmd_node->cmd_full[0], "cd", 3))
		ft_cd(minishell);
	 if (!ft_strncmp(cmd_node->cmd_full[0], "export", 7))
		ft_export(minishell);
	else if (!ft_strncmp(cmd_node->cmd_full[0], "env", 4))
	{
		
		ft_env(minishell);
	}
	else if (!ft_strncmp(cmd_node->cmd_full[0], "unset", 6))
		ft_unset(minishell);
	else if (!ft_strncmp(cmd_node->cmd_full[0], "exit", 5))
		ft_exit(minishell);
}

int	execute_command(t_minishell *minishell)
{
	int		i;
	int		status;
	int		exit_status;
	t_cmd	*node_cmd;
	t_pipex	*pipex;
	char	**env;

	node_cmd = minishell->cmd_node;
	pipex = minishell->pipex;
	env = minishell->env;
	while (node_cmd)
	{
		if (is_builtin_without_output(node_cmd))
			execute_builtin_without_output(minishell);
		else
			do_fork(minishell);
		node_cmd = node_cmd->next;
	}
	i = -1;
	close_fd(pipex);
	while (++i < pipex->cmd_count)
	{
		wait(&status);
		if (WIFEXITED(status) == 1)
		{
			exit_status = WEXITSTATUS(status);
			fprintf(stderr, C_YELLOW "parallel wait status = %d\n" C_RESET,
				(WEXITSTATUS(status)));
		}
	}
	signal(SIGINT, ft_newline);
	return (exit_status);
}
