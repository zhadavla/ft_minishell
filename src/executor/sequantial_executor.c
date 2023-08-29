// #include "../../includes/minishell.h"


// void	heredoc(t_pipex *pipex, int **heredoc_fd)
// {
// 	char	*line;

// 	while (1)
// 	{
// 		ft_printf("heredoc> ");
// 		line = get_next_line(0);
// 		if (!line)
// 			break ;
// 		if (!ft_strncmp(line, pipex->limiter, ft_strlen(pipex->limiter)))
// 		{
// 			free(line);
// 			break ;
// 		}
// 		close(heredoc_fd[0]);
// 		write(heredoc_fd[1], line, ft_strlen(line));
// 		close(heredoc_fd[1]);
// 		free(line);
// 	}
// }


// /**
//  * Executor to handle multiple heredocs
// */
// void	sequential_executor(t_pipex *pipex, t_cmd *node_cmd, char **env)
// {
// 	int pipe_fd[2];
// 	int heredoc_fd[2];

// 	if (pipe(pipe_fd) == -1 || pipe(heredoc_fd) == -1)
// 	{
// 		ft_putstr_fd("Pipe error\n", 2);
// 		exit(EXIT_FAILURE);
// 	}

// 	while (node_cmd)
// 	{
// 		int pid1 = fork();
// 		if (!pid1)
// 		{
// 			if (node_cmd->is_heredoc)
// 			{
// 				heredoc(node_cmd->delim, pipex, &heredoc_fd);
// 			if (node_cmd->infile_fd == 0)  // priority is for the last redirection
// 				node_cmd->infile_fd = heredoc_fd[0];
// 			}
// 			ft_dup2(node_cmd->infile_fd, node_cmd->outfile_fd);
// 			close_fd(pipex);
// 			ft_execute(node_cmd->cmd_full, env);
// 			close(node_cmd->infile_fd);
// 	    	close(node_cmd->outfile_fd);
// 			// exit(0); is it needed here? since we have execve function; 

// 		}
// 		else
// 			wait(NULL);
// 		node_cmd = node_cmd->next;
// 	}
// }