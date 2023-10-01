/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 20:50:18 by vzhadan           #+#    #+#             */
/*   Updated: 2023/10/01 14:17:04 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Returns array of paths to binaries
 */
char	**get_binaries(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		if (ft_strnstr(env[i], "PATH=", 5) != NULL)
			return (ft_split(ft_strnstr(env[i], "PATH=", 5), ':'));
	return (NULL);
}

int	check_paths(char **path, char *cmd, t_minishell *minishell)
{
	char	*pathname;
	int		i;

	i = -1;
	while (path[++i] != NULL)
	{
		pathname = ft_join(path[i], "/");
		pathname = ft_strjoin(pathname, cmd);
		if (access(pathname, F_OK) == 0)
		{
			if (access(pathname, X_OK) == 0)
			{
				free_split(path);
				free(pathname);
				return (TRUE);
			}
			ft_putstr_fd(C_RED "minishell: %s: Permission denied\n" C_RESET, 2);
			minishell->exit_status = 126;
			free_split(path);
			free(pathname);
			return (FALSE);
		}
		free(pathname);
	}
	return (FALSE);
}

/**
 * Returns TRUE if command is valid, FALSE otherwise
 */
int	ft_exec_validation(t_minishell *minishell)
{
	char	**path;
	char	*cmd;

	cmd = minishell->token->text;
	path = get_binaries(minishell->env);
	if (!path)
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		minishell->exit_status = 127;
		return (FALSE);
	}
	if (check_paths(path, cmd, minishell))
		return (TRUE);
	free_split(path);
	return (FALSE);
}

void	validate_absolute_path(t_token **token)
{
	t_token	*head;

	head = *token;
	while (head)
	{
		if ((head->text[0] == '/' || head->text[0] == '.')
			&& head->type == WORD)
		{
			if (access(head->text, F_OK) == 0)
			{
				if (access(head->text, X_OK) == 0)
					head->type = COMMAND;
				else
					head->type = WORD;
			}
			else
				head->type = WORD;
		}
		head = head->next;
	}
}
