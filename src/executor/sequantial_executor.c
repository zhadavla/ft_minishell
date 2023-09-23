/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequantial_executor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:16:01 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/23 19:02:49 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			create_pipe(int *pipex_pipe);
void		setup_file_descriptors(t_cmd *node_cmd, int *prev_read_end,
				int *pipex_pipe);

int	handle_delimiter(int fd[2], char *line, char *joined_line)
{
	write(fd[1], joined_line, ft_strlen(joined_line));
	free(joined_line);
	free(line);
	close(fd[1]);
	return (fd[0]);
}

static void	my_child(int sig)
{
	if (sig == SIGINT)
		exit(130);
}

void	seq_child(t_cmd *node_cmd, t_minishell *minishell, int pipex_pipe[2],
		int prev_read_end)
{
	if (node_cmd->exit_status != 0)
		exit(127);
	signal(SIGINT, my_child);
	setup_file_descriptors(node_cmd, &prev_read_end, pipex_pipe);
	if (node_cmd->is_builtin)
		ft_execute_builtin(minishell);
	else
		ft_execute(node_cmd->cmd_full, minishell->env);
	exit(0);
}

void	seq_parent(int *pipex_pipe, int *prev_read_end, int status,
		int *exit_status)
{
	signal(SIGINT, SIG_IGN);
	close(pipex_pipe[1]);
	wait(&status);
	if (WIFEXITED(status) == 1)
		*exit_status = WEXITSTATUS(status);
	if (*prev_read_end != -1)
		close(*prev_read_end);
	*prev_read_end = pipex_pipe[0];
	signal(SIGINT, ft_newline);
}

/**
 * Handles the sequential execution of commands
 */
int	sequential_executor(t_minishell *minishell)
{
	int		pipex_pipe[2];
	int		prev_read_end;
	int		exit_status;
	int		status;
	t_cmd	*node_cmd;

	status = 67;
	node_cmd = minishell->cmd_node;
	prev_read_end = -1;
	while (node_cmd)
	{
		if (create_pipe(pipex_pipe) == -1)
			return (-1);
		if (fork() == 0)
			seq_child(node_cmd, minishell, pipex_pipe, prev_read_end);
		else
			seq_parent(pipex_pipe, &prev_read_end, status, &exit_status);
		node_cmd = node_cmd->next;
	}
	return (exit_status);
}
