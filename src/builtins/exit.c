/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:21:34 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/22 22:07:10 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"	

int is_valid_argument(t_minishell *minishell)
{
	int i;
	char *str = minishell->cmd_node->cmd_full[1];

	if (!str)
		return (FALSE);
	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			minishell->exit_status = 255;
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

void ft_exit(t_minishell *minishell)
{
	int exit_status = 0;
	if (is_valid_argument(minishell))
	{
		if (minishell->cmd_node->cmd_full[1])
			exit_status = ft_atoi(minishell->cmd_node->cmd_full[1]);
		else
			exit_status = 0;
	}
	ft_putstr_fd("exit\n", 2);
	int i = -1;
	if (minishell->env)
	{
		while (minishell->env[++i]) 
			free(minishell->env[i]);
		free(minishell->env);
	}
	if (minishell->oldpwd)
		free(minishell->oldpwd);
	free_minishell(minishell);
	free(minishell);
	exit(exit_status);
}