/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_file_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 20:01:54 by vzhadan           #+#    #+#             */
/*   Updated: 2023/08/25 20:18:43 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int is_outfile(t_token *token)
{
	return (token->type == OUTFILE || token->type == OUTFILE_AP);
}

int is_infile(t_token *token)
{
	return (token->type == INFILE);
}

int is_file(t_token *token)
{
	return (is_outfile(token) || is_infile(token));
}

int	is_in_quotes(t_token *head)
{
	return ((head->quote == IN_QUOTE1 && head->next->quote == IN_QUOTE1)
		|| (head->quote == IN_QUOTE2 && head->next->quote == IN_QUOTE2));
}

bool	is_length_match(char *env_i, char *text)
{
	int	i;

	i = -1;
	while (env_i[++i] != '=')
		;
	return (i == ft_strlen(text));
}