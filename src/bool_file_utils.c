/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_file_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 20:01:54 by vzhadan           #+#    #+#             */
/*   Updated: 2023/08/25 20:29:15 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_outfile(t_token *token)
{
	return (token->type == OUTFILE || token->type == OUTFILE_AP);
}

int	is_infile(t_token *token)
{
	return (token->type == INFILE);
}

int	is_file(t_token *token)
{
	return (is_outfile(token) || is_infile(token));
}

int	is_length_match(char *env_i, char *text)
{
	int	i;

	i = -1;
	while (env_i[++i] != '=')
		;
	return (i == (int)ft_strlen(text));
}

int	is_unclosed_quotes(t_token **token)
{
	t_token	*head;
	int		double_flag;
	int		single_flag;

	head = *token;
	double_flag = 0;
	single_flag = 0;
	while (head->next)
	{
		if (head->type == DOUBLE_QUOTE)
			double_flag += 1;
		if (head->type == SINGLE_QUOTE)
			single_flag += 1;
		head = head->next;
	}
	if ((head->type == DOUBLE_QUOTE && double_flag % 2 == 0)
		|| (head->type == SINGLE_QUOTE && single_flag % 2 == 0))
		return (1);
	return (head->quote == IN_QUOTE1 || head->quote == IN_QUOTE2);
}
