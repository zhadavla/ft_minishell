/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 13:54:06 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/23 19:36:05 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clean_env(char **env);
void	ft_swap(char **a, char **b);
void	print_env(char **env);
int		ft_max(int a, int b);

void	create_env_copy_loop(t_env **head, t_env **tmp, char **env, int i)
{
	if (!(*head))
	{
		(*head) = (t_env *)malloc(sizeof(t_env));
		(*head)->next = NULL;
		(*head)->full_env = ft_strdup(env[i]);
		*tmp = *head;
	}
	else
	{
		(*tmp)->next = (t_env *)malloc(sizeof(t_env));
		*tmp = (*tmp)->next;
		(*tmp)->next = NULL;
		(*tmp)->full_env = ft_strdup(env[i]);
	}
}

t_env	*create_env_copy(char **env)
{
	t_env	*head;
	t_env	*tmp;
	int		i;

	head = NULL;
	tmp = NULL;
	i = -1;
	while (env[++i])
	{
		create_env_copy_loop(&head, &tmp, env, i);
		free(env[i]);
	}
	free(env);
	return (head);
}

/**
 * Transform env_list to env_array
 */
char	**t_env_to_array(t_env *env)
{
	char	**env_array;
	t_env	*tmp;
	int		i;

	env_array = NULL;
	tmp = env;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	env_array = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env)
	{
		env_array[i] = ft_strdup(env->full_env);
		i++;
		env = env->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

/**
 * Sorts env_list alphabetically by key
 * using insert sort
 */
void	print_env_sorted(char **env, int env_len)
{
	char	**sorted_env;
	int		i;
	int		j;
	int		len;

	sorted_env = (char **)malloc(sizeof(char *) * (env_len + 1));
	i = -1;
	while (++i < env_len)
		sorted_env[i] = ft_strdup(env[i]);
	sorted_env[env_len] = NULL;
	i = -1;
	while (++i < env_len)
	{
		j = -1;
		while (++j < i)
		{
			len = ft_max(ft_strlen(sorted_env[i]), ft_strlen(sorted_env[j]));
			if (ft_strncmp(sorted_env[i], sorted_env[j], len) < 0)
				ft_swap(&sorted_env[i], &sorted_env[j]);
		}
	}
	sorted_env[env_len] = NULL;
	print_env(sorted_env);
	clean_env(sorted_env);
}

int	ft_export(t_minishell *minishell)
{
	int		len;
	char	**commands;
	int		i;

	len = 0;
	commands = minishell->cmd_node->cmd_full;
	while (minishell->env[len])
		len++;
	if (!commands[1])
	{
		print_env_sorted(minishell->env, len);
		return (0);
	}
	minishell->env_list = create_env_copy(minishell->env);
	i = 0;
	while (commands[++i])
		add_env_variable(&minishell->env_list, commands[i]);
	minishell->env = t_env_to_array(minishell->env_list);
	free_env(minishell->env_list);
	return (0);
}
