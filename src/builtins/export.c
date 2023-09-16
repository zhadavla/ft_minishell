/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 13:54:06 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/16 14:51:54 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#define RED "\e[31m"
#define GREEN "\e[32m"
#define RESET "\e[0m"

t_env	*create_env_copy(char **env)
{
	t_env *head = NULL;
	t_env *tmp = NULL;
	int i = -1;
	while (env[++i])
	{	
		if (!head)
		{
			head = (t_env *)malloc(sizeof(t_env));
			head->next = NULL;
			head->key = ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]);
			head->value = ft_substr(env[i], ft_strchr(env[i], '=') - env[i] + 1,
					ft_strlen(env[i]) - (ft_strchr(env[i], '=') - env[i] + 1));
			fprintf(stderr, "\e[32mkey: %s\e[0m\n", head->key);
			fprintf(stderr, "\e[31mvalue: %s\e[0m\n", head->value);
			tmp = head;
		}
		else
		{
			tmp->next = (t_env *)malloc(sizeof(t_env));
			tmp = tmp->next;
			tmp->next = NULL;
			tmp->key = ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]);
			tmp->value = ft_substr(env[i], ft_strchr(env[i], '=') - env[i] + 1,
					ft_strlen(env[i]) - (ft_strchr(env[i], '=') - env[i] + 1));
			fprintf(stderr, "\e[32mkey: %s\e[0m\n", tmp->key);
			fprintf(stderr, "\e[31mvalue: %s\e[0m\n", tmp->value);
		}
	}
	return (head);
}