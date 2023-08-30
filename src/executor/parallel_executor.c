#include "../includes/minishell.h"

int ft_dup2(int fd1, int fd2)
{
	if (dup2(fd1, 0) == -1)
		return (-1);
	if (dup2(fd2, 1) == -1)
		return (-1);
	return (1);
}

void close_fd(t_pipex *pipex)
{
	int i;

	i = 0;
	// printf("pipex->fd_pipes_count = %d\n", pipex->fd_pipes_count);
	while (i < pipex->fd_pipes_count)
	{	
		// printf("pipex->fd_pipes[%d] = %d\n", i, pipex->fd_pipes[i]);
		close(pipex->fd_pipes[i]);
		i++;
	}
}

char *ft_join(char const *s1, char const *s2)
{
	size_t len1;
	size_t len2;
	char *str;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len1 + len2) + 1);
	if (!s1 || !s2)
		return (NULL);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, len1 + 1);
	ft_strlcat(str, s2, len2 + len1 + 1);
	return (str);
}

void free_split(char **strs)
{
	int i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

int ft_execute(char **full_cmd, char **env)
{
	char **path;
	char *pathname;
	int i;

	path = get_binaries(env);
	i = 0;
	while (path[i] != NULL)
	{
		pathname = ft_join(path[i], "/");
		pathname = ft_strjoin(pathname, full_cmd[0]);
		if (access(pathname, X_OK) == 0)
		{
			free_split(path);
			execve(pathname, full_cmd, env);
		}
		free(pathname);
		i++;
	}
	free_split(full_cmd);
	free_split(path);
	return (FALSE);
}

static void do_fork(t_pipex *pipex, t_cmd *node_cmd, char **env)
{
	int pid;
	int dup_check;
	int x ;

	pid = fork();
	dup_check = 1;
	
	if (pid == 0)
	{
	    dup_check = ft_dup2(node_cmd->infile_fd, node_cmd->outfile_fd);
		// printf("node_cmd->infile_fd = %d\n", node_cmd->infile_fd);
		// printf("node_cmd->outfile_fd = %d\n", node_cmd->outfile_fd);
	    close_fd(pipex);
	    ft_execute(node_cmd->cmd_full, env);
	}
	
	if (dup_check == -1)
	{
		write(2, "dup2 error\n", 11);
		exit(EXIT_FAILURE);
	}
}

void parallel_executor(t_pipex pipex, t_cmd **cmd_node, char **env)
{
	execute_command(&pipex, *cmd_node, env);
    if (pipex.cmd_count > 1)
        free(pipex.fd_pipes);
}

void execute_command(t_pipex *pipex, t_cmd *node_cmd, char **env)
{
	int i;
	int status;

	while (node_cmd)
	{
		do_fork(pipex, node_cmd, env);
		node_cmd = node_cmd->next;
	}

	close_fd(pipex);
	i = 0;
	while (++i < pipex->cmd_count)
		wait(&status);
}