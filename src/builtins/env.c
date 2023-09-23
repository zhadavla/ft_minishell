/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 18:12:01 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/23 19:15:52 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(t_minishell *minishell)
{
	char	**env;
	int		len;

	env = minishell->env;
	len = -1;
	while (env[++len])
	{
		printf("%s\n", env[len]);
		free(env[len]);
	}
	free(env);
}
