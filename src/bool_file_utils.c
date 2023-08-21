/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_file_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 20:01:54 by vzhadan           #+#    #+#             */
/*   Updated: 2023/08/21 20:12:00 by vzhadan          ###   ########.fr       */
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