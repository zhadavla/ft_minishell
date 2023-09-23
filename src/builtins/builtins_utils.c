/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 19:04:58 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/23 14:00:44 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Returns TRUE if command is a builtin, FALSE otherwise
 */
int	is_command_builtin(char *str_command)
{
	if (!ft_strncmp(str_command, "echo", ft_strlen("echo")))
		return (TRUE);
	else if (!ft_strncmp(str_command, "cd", ft_strlen("cd")))
		return (TRUE);
	else if (!ft_strncmp(str_command, "pwd", ft_strlen("pwd")))
		return (TRUE);
	else if (!ft_strncmp(str_command, "export", ft_strlen("export")))
		return (TRUE);
	else if (!ft_strncmp(str_command, "unset", ft_strlen("unset")))
		return (TRUE);
	else if (!ft_strncmp(str_command, "env", ft_strlen("env")))
		return (TRUE);
	else if (!ft_strncmp(str_command, "exit", ft_strlen("exit")))
		return (TRUE);
	return (FALSE);
}

/**
 * Checks if command is a builtin, changes token type to BUILTIN if it is
 */
void	validate_builtins(t_token **token)
{
	t_token	*head;

	head = *token;
	while (head)
	{
		if (is_command_builtin(head->text))
		{
			// // fprintf(stderr, "builtin: %s\n", head->text);
			head->type = BUILTIN;
		}
		head = head->next;
	}
}
