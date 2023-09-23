/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 14:17:56 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/23 18:39:44 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_execute_absolute_path(char **full_cmd, char **env)
{
	execve(full_cmd[0], full_cmd, env);
	free_split(full_cmd);
	return (TRUE);
}

int	ft_execute(char **full_cmd, char **env)
{
	char	**path;
	char	*pathname;
	int		i;

	if (full_cmd[0][0] == '/' || full_cmd[0][0] == '.')
		return (ft_execute_absolute_path(full_cmd, env));
	path = get_binaries(env);
	i = 0;
	while (path[i] != NULL)
	{
		pathname = ft_join(path[i], "/");
		pathname = ft_strjoin(pathname, full_cmd[0]);
		if (access(pathname, X_OK) == 0)
		{
			free_split(path);
			if (execve(pathname, full_cmd, env) == -1)
				return (FALSE);
		}
		free(pathname);
		i++;
	}
	free_split(full_cmd);
	free_split(path);
	return (FALSE);
}

int	ft_dup2(int fd1, int fd2)
{
	if (dup2(fd1, 0) == -1)
		return (-1);
	if (dup2(fd2, 1) == -1)
		return (-1);
	return (1);
}

void	close_fd(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->fd_pipes_count)
	{
		close(pipex->fd_pipes[i]);
		i++;
	}
}

char	*ft_join(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*str;

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
