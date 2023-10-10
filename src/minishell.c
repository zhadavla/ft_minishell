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

int	main(int argc, char **argv, char **env)
{
	t_minishell	*minishell;
	int			i;
	char		*line;

	(void)argc;
	(void)argv;
	minishell = malloc(sizeof(t_minishell));
	minishell->env = ft_dup_env(env);
	minishell->exit_status = 0;
	minishell->token = NULL;
	minishell->cmd_node = NULL;
	minishell->pipex = NULL;
	minishell->oldpwd = NULL;
	signal(SIGINT, ft_newline);
	signal(SIGQUIT, SIG_IGN);
	i = 0;
	while (TRUE)
	{
		line = readline("minishell$ ");
		add_history(line);
		if (!line)
		{
			free_minishell(minishell);
			free(line);
			printf("exit\n");
			break ;
		}
		if (is_only_spaces(line))
		{
			free_minishell(minishell);
			free(line);
			continue ;
		}
		minishell->token = lexer(line, minishell);
		if (!minishell->token)
		{
			free(line);

			continue ;
		}
		minishell->cmd_node = tokenizer(minishell->token, minishell);
		if (!minishell->cmd_node)
		{
			free(line);
			continue ;
		}
		is_command_in_every_pipe(&minishell->cmd_node);
		first_last_cmd(&(minishell->cmd_node));
		minishell->exit_status = executor(minishell);
		free(line);
		free_minishell(minishell);
	}
	i = -1;
	if (minishell->env)
	{
		while (minishell->env[++i])
			free(minishell->env[i]);
		free(minishell->env);
	}
	free(minishell->oldpwd);
	free(minishell);
	return (0);
}
