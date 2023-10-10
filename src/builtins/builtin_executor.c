/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 19:22:30 by vzhadan           #+#    #+#             */
/*   Updated: 2023/10/10 17:59:27 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_execute_builtin(t_minishell *minishell, t_cmd *node_cmd,  int is_seq)
{
	t_cmd	*cmd_node;
	(void)node_cmd;
	if (!node_cmd)
		cmd_node = minishell->cmd_node;
	else 
		cmd_node = node_cmd;
	if (!ft_strncmp(cmd_node->cmd_full[0], "pwd", 4))
		ft_pwd(minishell);
	else if (!ft_strncmp(cmd_node->cmd_full[0], "echo", 5))
		ft_echo(cmd_node->cmd_full);
	else if (!ft_strncmp(cmd_node->cmd_full[0], "env", 4))
		ft_env(minishell);
	else
	{
		ft_putstr_fd("command not found\n", 2);
		exit(EXIT_FAILURE);
	}
	if (cmd_node->next && !is_seq)
		free(minishell->pipex->fd_pipes);
	if (minishell->oldpwd)
		free(minishell->oldpwd);
	exit(EXIT_SUCCESS);
}