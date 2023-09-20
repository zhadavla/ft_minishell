/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallel_executor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:17:49 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/20 15:11:48 by mnurlybe         ###   ########.fr       */
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
		{
			fprintf(stderr, C_RED "555\n" C_RESET);
			exit(555);
		}
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

void	parallel_executor(t_minishell *minishell)
{
	execute_command(minishell->pipex, minishell->cmd_node, minishell->env);
	if (minishell->pipex->cmd_count > 1)
		free(minishell->pipex->fd_pipes);
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
	i = -1;
	close_fd(pipex);
	while (++i < pipex->cmd_count)
	{
		wait(&status);
		if (WIFEXITED(status) == 1)
			fprintf(stderr, C_YELLOW "wait status = %d\n" C_RESET,
				(WEXITSTATUS(status) % 256));
	}
	signal(SIGINT, ft_newline);
}
