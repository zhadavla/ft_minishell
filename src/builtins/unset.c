/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 19:38:57 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/23 19:38:59 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_env_node(t_env *env_head, t_env *to_remove)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = env_head;
	prev = NULL;
	while (tmp)
	{
		if (tmp == to_remove)
		{
			if (prev)
				prev->next = tmp->next;
			else
				env_head = tmp->next;
			free(tmp->full_env);
			free(tmp);
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int	ft_unset(t_minishell *minishell)
{
	t_cmd	*cmd_node;
	char	*key;
	t_env	*tmp;

	cmd_node = minishell->cmd_node;
	key = NULL;
	if (!cmd_node->cmd_full[1])
		return (0);
	minishell->env_list = create_env_copy(minishell->env);
	tmp = minishell->env_list;
	key = cmd_node->cmd_full[1];
	while (tmp)
	{
		if (!ft_strncmp(key, tmp->full_env, ft_strlen(key)))
		{
			remove_env_node(minishell->env_list, tmp);
			break ;
		}
		tmp = tmp->next;
	}
	minishell->env = t_env_to_array(minishell->env_list);
	free_env(minishell->env_list);
	return (0);
}
