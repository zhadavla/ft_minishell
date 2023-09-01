#include "../../includes/minishell.h"

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
		joined_line = ft_strjoin(joined_line, line);
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter)))
		{
			write(fd[1], joined_line, ft_strlen(joined_line));
			free(joined_line);
			free(line);
			close(fd[1]);
			break ;
		}
		free(line);
	}
	return (fd[0]);
}

/**
 * Executes commands in sequence to hangle multiple heredocs
 */
void	sequential_executor(t_cmd *node_cmd, char **env)
{
	int	pipex_pipe[2];
	int	pid;
	int	prev_read_end;
	int	hd_fd;

	prev_read_end = -1;
	while (node_cmd)
	{
		if (pipe(pipex_pipe) == -1)
		{
			perror("Pipe creation failed");
			return ;
		}
		pid = fork();
		if (pid == 0)
		{
			if (node_cmd->is_heredoc)
			{
				hd_fd = here_doc(node_cmd->delim);
				dup2(hd_fd, STDIN_FILENO);
				close(hd_fd);
			}
			close(pipex_pipe[0]);
			if (prev_read_end != -1 && !node_cmd->is_heredoc)
			{
				dup2(prev_read_end, STDIN_FILENO);
				close(prev_read_end);
			}
			if (node_cmd->next)
				dup2(pipex_pipe[1], STDOUT_FILENO);
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
