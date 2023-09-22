/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 19:22:30 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/22 17:33:45 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_execute_builtin(t_minishell *minishell)
{
	t_cmd	*cmd_node = minishell->cmd_node;
	char	**env = minishell->env;
	
	if (!ft_strncmp(cmd_node->cmd_full[0], "pwd", 3))
		ft_pwd(minishell);
	if (!ft_strncmp(cmd_node->cmd_full[0], "echo", 4))
		ft_echo(cmd_node->cmd_full);
	if (!ft_strncmp(cmd_node->cmd_full[0], "env", 3))
		ft_env(minishell);
	
	if (cmd_node->next)
		free(minishell->pipex->fd_pipes);
	free_minishell(minishell);
	free(minishell);
	exit(EXIT_SUCCESS);
}
