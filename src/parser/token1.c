/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 19:33:44 by vzhadan           #+#    #+#             */
/*   Updated: 2023/08/22 17:00:12 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_special_character(char c)
{
	return (!ft_isalnum(c) && c != '_');
}

/**
 * Adds new token to the end of the head
 */
void	t_add(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	sublexer(const char *str, int i, t_token **head, t_quote *q_s)
{
	t_token_type	token_type;

	token_type = update_token_type(str[i], str[i + 1]);
	if (str[i] == '\'' || str[i] == '\"')
		*q_s = update_q_s(str[i], *q_s);
	if ((*q_s == IN_QUOTE2 && token_type == DOUBLE_QUOTE) || (*q_s == IN_QUOTE1
			&& token_type == SINGLE_QUOTE))
		t_add(head, new_token(ft_substr(str, i, 1), 1, token_type, QUOTE0));
	else
		t_add(head, new_token(ft_substr(str, i, 1), 1, token_type, *q_s));
}

/*
 * if character is a special character, write whole word
 * (text before the special character) to the token
 * simoultaneously, write special char to another token
 * q_s is q_s :)
 */
t_token	*apply_lexer(char *str)
{
	t_token	*head;
	int		len;
	int		i;
	t_quote	q_s;

	head = NULL;
	len = 0;
	i = -1;
	q_s = QUOTE0;
	while (str[++i])
	{
		if (is_special_character(str[i]))
		{
			if (len > 0)
				t_add(&head, new_token(ft_substr(str, i - len, len), len, WORD,
						q_s));
			sublexer(str, i, &head, &q_s);
			len = 0;
		}
		else
			len++;
	}
	if (len > 0)
		t_add(&head, new_token(ft_substr(str, i - len, len), len, WORD, q_s));
	return (head);
}
