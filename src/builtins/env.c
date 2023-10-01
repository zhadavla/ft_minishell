/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 18:12:01 by vzhadan           #+#    #+#             */
/*   Updated: 2023/10/01 14:20:08 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(t_minishell *minishell)
{
	char	**env;
	int		len;

	if (!minishell->env ||
	 (minishell->cmd_node->cmd_full[1]))
	{
		fprintf(stderr, "smth went wrong\n");
		exit(47);
	}
	env = minishell->env;
	len = 0;
	while (env[len])
	{
		printf("%s\n", env[len]);
		len++;
		// free(env[len]);
	}
	// free(env);
}
