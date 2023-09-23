/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 13:54:06 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/23 18:17:39 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		if (!head)
		{
			head = (t_env *)malloc(sizeof(t_env));
			head->next = NULL;
			head->full_env = ft_strdup(env[i]);
			free(env[i]);
			// // fprintf(stderr, C_YELLOW "%s\n" C_RESET, head->full_env);
			// // fprintf(stderr, "\e[32mkey: %s\e[0m\n", head->key);
			// // fprintf(stderr, "\e[31mvalue: %s\e[0m\n", head->value);
			tmp = head;
		}
		else
		{
			tmp->next = (t_env *)malloc(sizeof(t_env));
			tmp = tmp->next;
			tmp->next = NULL;
			tmp->full_env = ft_strdup(env[i]);
			free(env[i]);
			// // fprintf(stderr, C_YELLOW "%s\n" C_RESET, tmp->full_env);
			// // fprintf(stderr, "\e[32mkey: %s\e[0m\n", tmp->key);
			// // fprintf(stderr, "\e[31mvalue: %s\e[0m\n", tmp->value);
		}
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
 * Adds new variable to env_list
 */
void	add_env_variable(t_env **env_list, char *env_text)
{
	t_env	*tmp;

	// // fprintf(stderr, C_YELLOW "env_text = %s\n" C_RESET, env_text);
	tmp = *env_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = (t_env *)malloc(sizeof(t_env));
	tmp = tmp->next;
	tmp->next = NULL;
	tmp->full_env = ft_strdup(env_text);
}

void	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("declare -x %s\n", env[i]);
		// // fprintf(stderr, C_YELLOW "%s\n" C_RESET, env[i]);
		i++;
	}
}

void	ft_swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	clean_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
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

	fprintf(stderr, "why???\n");
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
			len = ft_strlen(sorted_env[i]) > ft_strlen(sorted_env[j]) ? ft_strlen(sorted_env[i]) : ft_strlen(sorted_env[j]);
			if (ft_strncmp(sorted_env[i], sorted_env[j], len) < 0)
				ft_swap(&sorted_env[i], &sorted_env[j]);
		}
	}
	sorted_env[env_len] = NULL;
	// // fprintf(stderr, C_YELLOW "i = %d env_len = %d\n" C_RESET, i, env_len);
	print_env(sorted_env);
	clean_env(sorted_env);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->full_env);
		free(tmp);
	}
}

int	ft_export(t_minishell *minishell)
{
	int len = 0;
	char **commands = minishell->cmd_node->cmd_full;

	while (minishell->env[len])
	{
		fprintf(stderr, C_BLUE "%s\n" C_RESET, minishell->env[len]);
		len++;
	}
	if (!commands[1])
	{
		print_env_sorted(minishell->env, len);
		return (0);
	}

	minishell->env_list = create_env_copy(minishell->env);
	int i = 0;
	while (commands[++i])
		add_env_variable(&minishell->env_list, commands[i]);

	minishell->env = t_env_to_array(minishell->env_list);
	// print_env_in_yellow(minishell->env);
	free_env(minishell->env_list);
	return (0);
}