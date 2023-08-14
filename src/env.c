/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:43:02 by vzhadan           #+#    #+#             */
/*   Updated: 2023/08/14 14:03:28 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void merge_envs(t_token **token)
{
	t_token *head = *token;

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
