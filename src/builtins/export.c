/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 13:54:06 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/16 17:04:54 by vzhadan          ###   ########.fr       */
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
			// fprintf(stderr, C_YELLOW "%s\n" C_RESET, head->full_env);
			// fprintf(stderr, "\e[32mkey: %s\e[0m\n", head->key);
			// fprintf(stderr, "\e[31mvalue: %s\e[0m\n", head->value);
			tmp = head;
		}
		else
		{
			tmp->next = (t_env *)malloc(sizeof(t_env));
			tmp = tmp->next;
			tmp->next = NULL;
			tmp->full_env = ft_strdup(env[i]);
			// fprintf(stderr, C_YELLOW "%s\n" C_RESET, tmp->full_env);
			// fprintf(stderr, "\e[32mkey: %s\e[0m\n", tmp->key);
			// fprintf(stderr, "\e[31mvalue: %s\e[0m\n", tmp->value);
		}
	}
	return (head);
}

/**
 * Transform env_list to env_array
 */
char	**t_env_to_array(t_env *env)
{
	char **env_array = NULL;
	t_env *tmp = env;
	int i = 0;
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
void add_env_variable(t_env **env_list, char *env_text)
{
	t_env *tmp = *env_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = (t_env *)malloc(sizeof(t_env));
	tmp = tmp->next;
	tmp->next = NULL;
	tmp->full_env = ft_strdup(env_text);
}
