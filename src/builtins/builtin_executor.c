/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 19:22:30 by vzhadan           #+#    #+#             */
/*   Updated: 2023/10/01 14:30:47 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_execute_builtin(t_minishell *minishell, t_cmd *node_cmd,  int is_seq)
{
	t_cmd	*cmd_node;
	// int		i;
	(void)node_cmd;
	fprintf(stderr, "werehrerere\n");
	if (!node_cmd)
		cmd_node = minishell->cmd_node;
	else 
		cmd_node = node_cmd;
	if (!ft_strncmp(cmd_node->cmd_full[0], "pwd", 3))
		ft_pwd(minishell);
	if (!ft_strncmp(cmd_node->cmd_full[0], "echo", 4))
		ft_echo(cmd_node->cmd_full);
	if (!ft_strncmp(cmd_node->cmd_full[0], "env", 3))
		ft_env(minishell);
	if (cmd_node->next && !is_seq)
		free(minishell->pipex->fd_pipes);
	// i = -1;
	// if (minishell->env && minishell->cmd_node->cmd_full[1])
	// // if (minishell->env)
	// {
	// 	while (minishell->env[++i])
	// 		free(minishell->env[i]);
	// 	free(minishell->env);
	// }
	if (minishell->oldpwd)
		free(minishell->oldpwd);
	// free_minishell(minishell);
	// free(minishell);
	exit(EXIT_SUCCESS);
}
