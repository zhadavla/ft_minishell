/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:43:02 by vzhadan           #+#    #+#             */
/*   Updated: 2023/08/14 14:49:38 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Merge env variables with words
 * also update len of token
*/
void	merge_envs(t_token **token)
{
	t_token	*head;

	head = *token;
	while (head)
	{
		if (head->type == ENV_VARIBLE)
		{
			if (head->next->type == WORD)
			{
				head->text = ft_strjoin(head->text, head->next->text);
				head->len = ft_strlen(head->text);
				head->next = head->next->next;
			}
		}
		head = head->next;
	}
}

bool	is_length_match(char *env_i, char *text)
{
	int	i;

	i = -1;
	while (env_i[++i] != '=')
		;
	return (i == ft_strlen(text));
}

/**
 * Find env variable in env array
 * Return value of env variable
 * Empty string if not found
 * It should compare length of text and env variable
 * and only if they are equal compare the strings
 */
char	*get_env_value(char *text, char **env)
{
	int		i;
	char	*env_found;

	i = 0;
	while (env[++i])
		if ((env_found = ft_strnstr(env[i], text + 1, ft_strlen(text)))
			&& is_length_match(env_found, text + 1))
			return (ft_strnstr(env[i], text + 1, ft_strlen(text) + 1));
	return (ft_strdup(""));
}

/**
 * Replace $ENV with value from env in each token
 */
void	expand_env(t_token **token, char **env)
{
	t_token	*head;
	char	*env_value;

	head = *token;
	while (head)
	{
		if (head->type == ENV_VARIBLE)
		{
			env_value = get_env_value(head->text, env);
			printf("env_value: %s\n", env_value);
			if (env_value)
			{
				head->text = ft_strdup(env_value);
				head->len = ft_strlen(head->text);
			}
		}
		head = head->next;
	}
}
