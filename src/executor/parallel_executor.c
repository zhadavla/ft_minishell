/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallel_executor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:17:49 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/20 15:52:59 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	my_child(int sig)
{
	if (sig == SIGINT)
	{
		fprintf(stderr, C_RED "child exit\n" C_RESET);
		exit(130);
	}
}

static void	do_fork(t_pipex *pipex, t_cmd *node_cmd, char **env)
{
	int	pid;
	int	dup_check;
	int	x;

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
			ft_execute_builtin(node_cmd, env);
		}
		else if (!ft_execute(node_cmd->cmd_full, env))
			exit(42);
	}
	signal(SIGINT, SIG_IGN);
	fprintf(stderr, C_GREEN "after exit\n" C_RESET);
}

int	parallel_executor(t_minishell *minishell)
{
	int exit;
	exit = execute_command(minishell->pipex, minishell->cmd_node, minishell->env);
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
		return (!ft_strncmp(cmd, "cd", 5)
			|| !ft_strncmp(cmd, "export", 7)
			|| !ft_strncmp(cmd, "unset", 6)
			|| !ft_strncmp(cmd, "exit", 5));
	}
	return (FALSE);
}

void execute_builtin_without_output(t_cmd *cmd_node, char **env)
{
	// if (!ft_strncmp(cmd_node->cmd_full[0], "cd", 5))
	// 	ft_cd(cmd_node, env);
	// else if (!ft_strncmp(cmd_node->cmd_full[0], "export", 7))
	// 	ft_export(cmd_node, env);
	// else if (!ft_strncmp(cmd_node->cmd_full[0], "unset", 6))
	// 	ft_unset(cmd_node, env);
	if (!ft_strncmp(cmd_node->cmd_full[0], "exit", 5))
		ft_exit(cmd_node);
}

void	execute_command(t_pipex *pipex, t_cmd *node_cmd, char **env)
{
	int	i;
	int	status;

	while (node_cmd)
	{
		if (is_builtin_without_output(node_cmd))
			execute_builtin_without_output(node_cmd, env);
		else
			do_fork(pipex, node_cmd, env);
		node_cmd = node_cmd->next;
	}
	i = -1;
	close_fd(pipex);
	while (++i < pipex->cmd_count)
	{
		wait(&status);
		if (WIFEXITED(status) == 1)
		{
			fprintf(stderr, C_YELLOW "parallel wait status = %d\n" C_RESET,
				(WEXITSTATUS(status)));
		}
	}
	signal(SIGINT, ft_newline);
	return (WEXITSTATUS(status));
}
