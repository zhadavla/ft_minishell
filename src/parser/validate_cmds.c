/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 20:50:18 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/19 19:27:33 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Returns array of paths to binaries
 */
char	**get_binaries(char **env)
{
	return (ft_split(getenv("PATH"), ':'));
}

/**
 * Returns TRUE if command is valid, FALSE otherwise
 */
static int	ft_exec_validation(t_minishell *minishell)
{
	char	**path;
	char	*pathname;
	int		i;
	char	*cmd;

	cmd = minishell->token->text;
	path = get_binaries(minishell->env);
	i = 0;
	while (path[i] != NULL)
	{
		pathname = ft_join(path[i], "/");
		pathname = ft_strjoin(pathname, cmd);
		if (access(pathname, F_OK) == 0)
		{
			if (access(pathname, X_OK) == 0)
			{
				fprintf(stderr, "command found 6666 {%s}\n", pathname);
				free_split(path);
				free(pathname);
				return (TRUE);
			}
			fprintf(stderr, "minishell: %s: Permission denied\n", cmd);
			// minishell->exit_status = 126;
			// return (FALSE);
		}
		free(pathname);
		i++;
	}
	free_split(path);
	return (FALSE);
}

void	validate_absolute_path(t_token **token)
{
	t_token	*head;

	head = *token;
	while (head)
	{
		// error_msg("validate_absolute_path");
		// fprintf(stderr, "head->text[0] = %s\n", head->text);
		if ((head->text[0] == '/' || head->text[0] == '.')
			&& head->type == WORD)
		{
			if (access(head->text, F_OK) == 0)
			{
				if (access(head->text, X_OK) == 0)	
					head->type = COMMAND;
				else
					head->type = WORD;
			}
			else
				head->type = WORD;
		}
		head = head->next;
	}
}
/**
 * later: don't forget to handle wrong command input
 * and return error message: "command not found"
 * */
void	validate_commands(t_minishell *minishell)
{
	t_token	*head;

	head = minishell->token;
	while (head)
	{
		if (head->type == WORD && ft_exec_validation(minishell) == TRUE)
		{
			fprintf(stderr, "command found {%s}\n", head->text);	
			head->type = COMMAND;
		}
		else if (head->type == ENV_VARIBLE || (head->type == WHITE_SPACE
				&& head->quote != QUOTE0))
			head->type = WORD;
		head = head->next;
		minishell->token = head;
	}
}

void	validate_filename(t_token **token)
{
	t_token	*head;

	head = *token;
	while (head)
	{
		if (head->next && (head->next->type == WORD
				|| head->next->type == COMMAND))
		{
			if (head->type == REDIR_APPEND)
				head->next->type = OUTFILE_AP;
			else if (head->type == REDIR_OUT)
				head->next->type = OUTFILE;
			else if (head->type == REDIR_IN)
				head->next->type = INFILE;
		}
		head = head->next;
	}
}

void	validate_commands_two(t_token **token)
{
	t_token	*head;

	head = *token;
	while (head)
	{
		if (head->next && head->type == COMMAND && head->next->type == COMMAND)
			head->next->type = WORD;
		head = head->next;
	}
}
