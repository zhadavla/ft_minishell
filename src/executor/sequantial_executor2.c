/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequantial_executor2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 18:54:28 by vzhadan           #+#    #+#             */
/*   Updated: 2023/10/10 18:01:28 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		handle_delimiter(int fd[2], char *line, char *joined_line);

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
		if (!line)
		{
			close(fd[1]);
			break ;
		}
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter)))
			return (handle_delimiter(fd, line, joined_line));
		joined_line = ft_strjoin(joined_line, line);
		free(line);
	}
	return (fd[0]);
}

/**
 * Handles setting up file descriptors
 */
void	setup_file_descriptors(t_cmd *node_cmd, int *prev_read_end,
		int *pipex_pipe)
{
	int	hd_fd;

	hd_fd = 42;
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
