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

void	init_minishell(t_minishell **minishell, char **env)
{
	(*minishell) = malloc(sizeof(t_minishell));
	(*minishell)->env = ft_dup_env(env);
	(*minishell)->exit_status = 0;
	(*minishell)->token = NULL;
	(*minishell)->cmd_node = NULL;
	(*minishell)->pipex = NULL;
	(*minishell)->oldpwd = NULL;
	(*minishell)->is_builtin_wo_command = 0;
}

void	free_program(t_minishell **minishell)
{
	int			i;

	i = -1;
	if ((*minishell)->env)
	{
		while ((*minishell)->env[++i])
			free((*minishell)->env[i]);
		free((*minishell)->env);
	}
	free((*minishell)->oldpwd);
	free((*minishell));
}

int	is_empty_line(char *line, t_minishell **minishell)
{
	if (!line)
	{
		free_minishell(*minishell);
		free(line);
		printf("exit\n");
		return (1);
	}
	return (0);
}

void validate_builtin_without_output_command(t_minishell *minishell);

int	main(int argc, char **argv, char **env)
{
	t_minishell	*minishell;
	char		*line;

	(void)argc;
	(void)argv;
	minishell = NULL;
	init_minishell(&minishell, env);
	signal(SIGINT, ft_newline);
	signal(SIGQUIT, SIG_IGN);
	while (TRUE)
	{
		line = readline("minishell$ ");
		minishell->is_builtin_wo_command = 0;
		add_history(line);
		if (is_empty_line(line, &minishell))
			break ;
		if (is_only_spaces(line))
		{
			free_minishell(minishell);
			free(line);
			continue ;
		}
		if (!lexer_tokenizer(&minishell, line))
			continue ;
		validate_builtin_without_output_command(minishell);
		is_command_in_every_pipe(&minishell->cmd_node);
		first_last_cmd(&(minishell->cmd_node));
		minishell->exit_status = executor(minishell);
		free(line);
		free_minishell(minishell);
	}
	free_program(&minishell);
	return (0);
}
