/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 19:22:30 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/16 19:50:33 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_execute_builtin(t_cmd *cmd_node, char **env)
{
	if (!ft_strncmp(cmd_node->cmd_full[0], "export", 7)){
		fprintf(stderr, C_YELLOW "export\n" C_RESET);
	
		// int i = 0;
		// while (env[i]){i++;}
	
		// env[i] = ft_strdup("DUPPED_TEXT:42");
		// i++;
		// env[i] = NULL;
		ft_export(cmd_node->cmd_full, env);
	}
	if (!ft_strncmp(cmd_node->cmd_full[0], "echo", 4))
		ft_echo(cmd_node->cmd_full);
}
