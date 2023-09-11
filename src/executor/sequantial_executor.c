/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequantial_executor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:16:01 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/11 17:09:45 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_delimiter(int fd[2], char *line, char *joined_line)
{
	write(fd[1], joined_line, ft_strlen(joined_line));
	free(joined_line);
	free(line);
	close(fd[1]);
	return (fd[0]);
}

/**
 * Reads from input untill the delimiter is found
 * and writes the input to the pipe
 * Returns the read end of the pipe
 */
int	here_doc(char *delimiter)
{
	int		fd[2];
	char	*line;
	char	*joined_line;

	line = NULL;
	joined_line = ft_strdup("");
	pipe(fd);
	while (1)
	{
		ft_printf("heredoc> ");
		line = get_next_line(0);
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter)))
			return (handle_delimiter(fd, line, joined_line));
		if (!line)
		{
			close(fd[1]);
			break ;
		}
		joined_line = ft_strjoin(joined_line, line);
		free(line);
	}
	return (fd[0]);
}

/**
 * Handles setting up file descriptors
 */
void	setup_file_descriptors(t_cmd *node_cmd, int *prev_read_end,
		int *pipex_pipe, int hd_fd)
{
	if (node_cmd->is_heredoc)
	{
		hd_fd = here_doc(node_cmd->delim);
		dup2(hd_fd, STDIN_FILENO);
		close(hd_fd);
	}
	close(pipex_pipe[0]);
	if (*prev_read_end != -1 && !node_cmd->is_heredoc)
	{
		dup2(*prev_read_end, STDIN_FILENO);
		close(*prev_read_end);
	}
	if (node_cmd->next)
		dup2(pipex_pipe[1], STDOUT_FILENO);
	if (node_cmd->infile_fd != 0)
		dup2(node_cmd->infile_fd, STDIN_FILENO);
	if (node_cmd->outfile_fd != 1)
		dup2(node_cmd->outfile_fd, STDOUT_FILENO);
}

/**
 * Creates a pipe
 */
int	create_pipe(int *pipex_pipe)
{
	if (pipe(pipex_pipe) == -1)
	{
		perror("Pipe creation failed");
		return (-1);
	}
	return (0);
}

/**
 * Handles the sequential execution of commands
 */
void	sequential_executor(t_cmd *node_cmd, char **env)
{
	int	pipex_pipe[2];
	int	prev_read_end;
	int	hd_fd;

	prev_read_end = -1;
	while (node_cmd)
	{
		if (create_pipe(pipex_pipe) == -1)
			return ;
		if (fork() == 0)
		{
			setup_file_descriptors(node_cmd, &prev_read_end, pipex_pipe, hd_fd);
			ft_execute(node_cmd->cmd_full, env);
			exit(0);
		}
		else
		{
			close(pipex_pipe[1]);
			wait(NULL);
			if (prev_read_end != -1)
				close(prev_read_end);
			prev_read_end = pipex_pipe[0];
		}
		node_cmd = node_cmd->next;
	}
}
