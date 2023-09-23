/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 19:37:31 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/23 19:41:02 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(t_minishell *minishell)
{
	char	*cwd;
	t_cmd	*cmd_node;

	cwd = getcwd(NULL, 0);
	cmd_node = minishell->cmd_node;
	if (cwd == NULL)
	{
		cmd_node->exit_status = 69;
		return ;
	}
	printf("%s\n", cwd);
	free(cwd);
}
