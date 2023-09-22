/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:43:02 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/22 16:01:25 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_env_value(char *text, char **env, t_minishell *minishell);

/**
 * Merge env variables with words
 * also update len of token
 */
void	merge_envs(t_token **token)
{
	t_token	*head;
	t_token	*tmp;

	head = *token;
	while (head)
	{
		if (head->type == ENV_VARIBLE)
		{
			if (ft_strncmp(head->text, "~", 2) == 0)
			{
				free(head->text);
				head->text = ft_strdup("$HOME");
			}
			else if (head->next->type == WORD
				&& !is_special_character(head->next->text[0]))
			{
				head->text = ft_strjoin(head->text, head->next->text);
				head->len = ft_strlen(head->text);
				tmp = head->next;
				head->next = head->next->next;
				free_token(tmp);
			}
		}
		head = head->next;
	}
}

/**
 * Replace $ENV with value from env in each token
 */
void	expand_env(t_token **token, char **env, t_minishell *minishell)
{
	t_token	*head;
	char	*env_value;
	char	*text_tmp;

	head = *token;
	while (head)
	{
		if (head->type == ENV_VARIBLE && head->quote != IN_QUOTE1
			&& !is_special_character(head->text[1]))
		{
			env_value = get_env_value(head->text, env, minishell);
			text_tmp = ft_strdup(head->text);
			free(head->text);
			if (env_value)
			{
				head->text = ft_strdup(env_value);
				if (*(text_tmp + 1) == '?')
					free(env_value);
			}
			else
				head->text = ft_strdup("");
			free(text_tmp);
			head->len = ft_strlen(head->text);
		}
		head = head->next;
	}
}

/**
 * Find env variable in env array
 * Return value of env variable
 * Empty string if not found
 * It should compare length of text and env variable
 * and only if they are equal compare the strings
 */
static char	*get_env_value(char *text, char **efnv, t_minishell *minishell)
{
	int		i;
	char	*env_found;
	char **env = minishell->env;
	i = 0;
	while (env[++i])
	{
		if (*(text+1) == '?')
		{
			fprintf(stderr, C_YELLOW "exit status = %d\n" C_RESET,
					minishell->exit_status);
			return (ft_itoa(minishell->exit_status));
		}
		env_found = ft_strnstr(env[i], text + 1, ft_strlen(text));
		if (env_found && is_length_match(env_found, text + 1))
			return (env_found + ft_strlen(text));
	}
	return (NULL);
}

/**
 * ????
 */
void	validate_dollarsign(t_token **token)
{
	t_token	*head;

	head = *token;
	while (head)
	{
		if (head->type == WORD && head->text[0] == '$' && head->text[1] == '?'
			&& head->quote != IN_QUOTE1)
			head->type = DOLLAR_SIGN;
		head = head->next;
	}
}
