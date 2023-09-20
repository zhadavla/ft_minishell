/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:21:34 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/20 19:21:35 by vzhadan          ###   ########.fr       */
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

int ft_exit(t_minishell *minishell)
{
	if (is_valid_argument(minishell))
	{
		if (minishell->cmd_node->cmd_full[1])
			minishell->exit_status = ft_atoi(minishell->cmd_node->cmd_full[1]);
		else
			minishell->exit_status = 0;
	}
	ft_putstr_fd("exit\n", 2);
	free_minishell(minishell);
	exit(minishell->exit_status);
}