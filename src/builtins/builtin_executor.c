/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 19:22:30 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/23 18:11:43 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_execute_builtin(t_minishell *minishell)
{
	t_cmd	*cmd_node = minishell->cmd_node;
	
	if (!ft_strncmp(cmd_node->cmd_full[0], "pwd", 3))
		ft_pwd(minishell);
	if (!ft_strncmp(cmd_node->cmd_full[0], "echo", 4))
		ft_echo(cmd_node->cmd_full);
	if (!ft_strncmp(cmd_node->cmd_full[0], "env", 3))
		ft_env(minishell);
	
	if (cmd_node->next)
		free(minishell->pipex->fd_pipes);
	int i = -1;
	if (minishell->env && minishell->cmd_node->cmd_full[1])
	{
		while (minishell->env[++i]) 
			free(minishell->env[i]);
		free(minishell->env);
	}
	if (minishell->oldpwd)
		free(minishell->oldpwd);
	free_minishell(minishell);
	free(minishell);
	exit(EXIT_SUCCESS);
}
