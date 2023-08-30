#include "../../includes/minishell.h"


// void	heredoc(t_pipex *pipex, char *delim, int *out_fd)
// {
// 	char	*line;
// 	char *joined_line = NULL;

// 	printf("fd = %d\n", *out_fd);
// 	while (1)
// 	{
// 		ft_printf("heredoc> ");

// 		line = get_next_line(0);

// 		if (!line)
// 			break ;
// 		if (!ft_strncmp(line, delim, ft_strlen(delim)))
// 		{
// 			free(line);
// 			break ;
// 		}
// 		write(*out_fd, line, ft_strlen(line));
// 		printf("here\n");
// 		// close(*out_fd);

// 		free(line);
// 	}
// 	// close(*out_fd);
// }


/**
 * Executor to handle multiple heredocs
*/
// void	sequential_executor(t_pipex *pipex, t_cmd *node_cmd, char **env)
// {
// 	// int pipe_fd[2];
// 	int hd_fd[2];
// 	char	*line;

// 	if (pipe(hd_fd) == -1)
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
// 				// close(hd_fd[0]);
// 				// heredoc(pipex, node_cmd->delim, &(hd_fd[1]));
// 				while (1)
// 				{
// 					ft_printf("heredoc> ");

// 					line = get_next_line(0);

// 					if (!line)
// 						break ;
// 					if (!ft_strncmp(line, node_cmd->delim, ft_strlen(node_cmd->delim)))
// 					{
// 						free(line);
// 						break ;
// 					}
// 					write(hd_fd[1], line, ft_strlen(line));
// 					free(line);
// 				}
// 			// if (node_cmd->infile_fd == 0)  // priority is for the last redirection
// 				node_cmd->infile_fd = hd_fd[0];
				
// 			}
// 			ft_dup2(node_cmd->infile_fd, node_cmd->outfile_fd);
// 			// close_fd(pipex);

// 			char *tmp = malloc(100);

// 			read(node_cmd->infile_fd, tmp, 100);
// 			printf("tmp = {%s}\n", tmp);
		
// 			ft_execute(node_cmd->cmd_full, env);

// 			// exit(0); // is it needed here? since we have execve function;

// 		}
// 		else
// 			wait(NULL);
// 		node_cmd = node_cmd->next;
// 	}
// }

void foo()
{
    // This is the child process
            
            // if (node_cmd->is_heredoc) {
            //     joined_line = ft_strdup(""); // Initialize joined_line for each command
                
            //     while (1) {
            //         ft_printf("heredoc> ");
            //         line = get_next_line(0);
                    
            //         if (!line) {
            //             break;
            //         }
                    
            //          if (!ft_strncmp(line, node_cmd->delim, ft_strlen(node_cmd->delim))) {
            //             write(hd_pipe[1], joined_line, ft_strlen(joined_line));
            //             free(joined_line);
            //             free(line);
            //             break;
            //         }
                    
            //         joined_line = ft_strjoin(joined_line, line);
            //         free(line);
            //     }
            //     node_cmd->infile_fd = hd_pipe[0];
            //     close(hd_pipe[1]); // Close write end of pipe
            // }

}
int here_doc(char *delimiter) {
    int fd[2];
    char *line = NULL;
    char *joined_line = ft_strdup("");
    pipe(fd);
    
    while (1) {
        ft_printf("heredoc> ");
        line = get_next_line(0);
        
        if (!line) {
            close(fd[1]); // Close the write end of the pipe before returning
            break;
        }
        
        joined_line = ft_strjoin(joined_line, line);
        
        if (!ft_strncmp(line, delimiter, ft_strlen(delimiter))) {
            write(fd[1], joined_line, ft_strlen(joined_line));
            free(joined_line);
            free(line);
            close(fd[1]); // Close the write end of the pipe
            break;
        }
        
        free(line);
    }
    
    return fd[0]; // Return the read end of the pipe
}

void sequential_executor(t_pipex *pipex, t_cmd *node_cmd, char **env) {
    int pipex_pipe[2];
    int pid; 
    int prev_read_end = -1;

    while (node_cmd) {
        if (pipe(pipex_pipe) == -1) {
            perror("Pipe creation failed");
            return;
        }
        
        pid = fork();

        if (pid == 0) {
            if (node_cmd->is_heredoc) {
                int hd_fd = here_doc(node_cmd->delim);
                printf("hd fd = %d\n", hd_fd);
                dup2(hd_fd, STDIN_FILENO);
                close(hd_fd); // Close the read end of the pipe after redirection
            }   

            close(pipex_pipe[0]);
            
            if (prev_read_end != -1 && !node_cmd->is_heredoc) {
                dup2(prev_read_end, STDIN_FILENO);
                close(prev_read_end);
            }

            if (node_cmd->next)
                dup2(pipex_pipe[1], STDOUT_FILENO);
            
            ft_execute(node_cmd->cmd_full, env);
            exit(0); // Terminate child process after command execution
        }
        else {
            close(pipex_pipe[1]);
            wait(NULL);
            
            if (prev_read_end != -1) {
                close(prev_read_end);
            }
            
            prev_read_end = pipex_pipe[0];
        }
        
        node_cmd = node_cmd->next;
    }
}
