/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 20:50:18 by vzhadan           #+#    #+#             */
/*   Updated: 2023/08/19 18:58:43 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_split(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

char	**get_binaries(char **env)
{
	int	i;

	i = 0;
	while (env[++i])
		if (ft_strnstr(env[i], "PATH=", 5))
			return (ft_split(env[i] + 5, ':'));
	return (NULL);
}

char	*ft_join(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*str;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len1 + len2) + 1);
	if (!s1 || !s2)
		return (NULL);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, len1 + 1);
	ft_strlcat(str, s2, len2 + len1 + 1);
	return (str);
}

int	ft_execute(char *cmd, char **env)
{
	char	**path;
	char	*pathname;
	int		i;

	path = get_binaries(env);
	i = 0;
	while (path[i] != NULL)
	{
		pathname = ft_join(path[i], "/");
		pathname = ft_strjoin(pathname, cmd);
		if (access(pathname, X_OK) == 0)
		{
			free_split(path);
			free(pathname);
			return (TRUE);
		}
		free(pathname);
		i++;
	}
	free_split(path);
	return (FALSE);
}

// later: don't forget to handle wrong command input and return error message: "command not found"
void	validate_commands(t_token **token, char **g_env)
{
	t_token	*head;

	head = *token;
	while (head)
	{
		if (head->type == WORD && ft_execute(head->text, g_env) == TRUE)
			head->type = COMMAND;
		// else if (head->type == WORD && ft_execute(head->text, g_env) == FALSE)
		// {
		// 	write(2, "Command not found\n", 18);
		// 	free_tokens(head);
		// 	exit(EXIT_SUCCESS);
		// }
		else if (head->type == ENV_VARIBLE)
			head->type = WORD;
		head = head->next;
	}
}

void validate_filename(t_token **token)
{
	t_token *head;

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

void validate_commands_two(t_token **token)
{
	t_token *head;

	head = *token;
	while (head)
	{
		if (head->next && head->type == COMMAND && head->next->type == COMMAND)
			head->next->type = WORD;
		head = head->next;
	}
}
