#include "../includes/minishell.h"

static int count_commands(t_cmd *cmd)
{
    int count;

    count = 0;
    while (cmd)
    {
        count++;
        cmd = cmd->next;
    }
    return (count);
}

/**
 * initialize the pipex struct
*/
static void	init_pipex(t_pipex *pipex, t_cmd *cmd_head)
{
    if (!cmd_head)
        return ;
    pipex->cmd_count = count_commands(cmd_head);
    printf("cmd_count = %d\n", pipex->cmd_count);
    pipex->fd_pipes_count = (pipex->cmd_count - 1) * 2;
    pipex->fd_pipes = (int *)malloc(sizeof(int) * pipex->fd_pipes_count);
}

/**
 * print the file descriptors stored into the pipex->fd_pipes array
*/
int	create_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->fd_pipes_count)
	{
		if (pipe(pipex->fd_pipes + i) == -1)
		{
			free(pipex->fd_pipes);
			return (-1);
		}
		i += 2;
	}
    // printf pipex->fd_pipes fds
    printf("\n\nfd_pipes: \n");
    for (int i = 0; i < pipex->fd_pipes_count; i++)
        printf("{fd %d: %d} \n", i, pipex->fd_pipes[i]);
	return (1);
}


/**
 * update the infile_fd and outfile_fd for each command node;
 * if there is stdin or stdout redirections, then the infile_fd or outfile_fd
 * will be updated to the corresponding file descriptor from the pipe;
 * except for the first and last command, the infile_fd and outfile_fd will be
 * updated to the corresponding file descriptor stored in open_files() function;
*/
void    update_pipe_fds(t_cmd **cmd_node)
{
    t_pipex pipex;
    t_cmd *head;

    head = *cmd_node;
    if (count_commands (*cmd_node) == 1)
        return ;

    init_pipex(&pipex, *cmd_node);
    // if (create_pipes(&pipex) == -1)
    //     return ;  error handling when creating pipes
    create_pipes(&pipex);
    int i = 0;

    while (head)
    {
        if (head->is_first && head->outfile_fd == 1)
            head->outfile_fd = pipex.fd_pipes[1];
        else if (head->is_last && head->infile_fd == 0)
            head->infile_fd = pipex.fd_pipes[pipex.fd_pipes_count - 2];
        else
        {
            if (head->infile_fd == 0)
                head->infile_fd = pipex.fd_pipes[i];
            if (head->outfile_fd == 1)
                head->outfile_fd = pipex.fd_pipes[i + 3];
            i += 2;
        }
        head = head->next;
    }
}

/**
 * update the is_first and is_last flags for each command node
*/
void first_last_cmd(t_cmd **cmd_node)
{
    t_cmd *head;

    head = *cmd_node;
    
    head->is_first = 1;
    head = head->next;
    while (head)
    {
        if (head->next == NULL)
            head->is_last = 1;
        head = head->next;
    }
}