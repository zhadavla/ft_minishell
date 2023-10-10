#include "../includes/minishell.h"
#include <assert.h>
#include <stdio.h>

t_token	*lexer(char *line, t_minishell *minishell)
{
	t_token	*head;

	head = apply_lexer(line);
	if (is_unclosed_quotes(&head))
	{
		write(2, "Unclosed quotes\n", 16);
		free_tokens(head);
		minishell->exit_status = 2;
		return (0);
	}
	return (head);
}

t_cmd	*tokenizer(t_token *head, t_minishell *minishell)
{
	t_cmd	*cmd_node;
	t_cmd	*tmp;

	merge_envs(&head);
	expand_env(&head, minishell);
	concatenate_minus(&head);
	concate_quotes(&head);
	merge_redirections_heredoc(&head);
	validate_absolute_path(&head);
	validate_commands(minishell);
	if (!is_quote_error(&head))
	{
		write(2, "syntax error near unexpected token `newline'1\n", 46);
		free_tokens(head);
		minishell->exit_status = 2;
		return (0);
	}
	remove_quotes(&head);
	concate_leftover_strings(&head);
	remove_whitespaces(&head);
	validate_filename(&head);
	if (validate_heredoc(&head, minishell))
		return (0);
	validate_dollarsign(&head);
	validate_commands_two(&head);
	validate_builtins(&head);
	if (head->type == WORD)
	{
		write(2, "syntax error near unexpected token `newline'2\n", 46);
		free_tokens(head);
		minishell->exit_status = 127;
		return (0);
	}
	// print_tokens(head);
	cmd_node = split_to_pipes(&head);
	tmp = cmd_node;
	while (tmp)
	{
		if (!tmp->is_heredoc && !tmp->cmd_full[0])
		{
			write(2, "COMMAND NOT FOUND (HD)\n", 23);
			free_cmd_nodes(&cmd_node);
			free_tokens(head);
			minishell->exit_status = 56;
			return (0);
		}
		tmp = tmp->next;
	}
	free_tokens(head);
	return (cmd_node);
}

// void executor(t_cmd *cmd_node, char **env, t_token *head, t_env **env_list)
int	executor(t_minishell *minishell)
{
	t_pipex	pipex;

	if (open_files(&minishell->cmd_node))
	{
		fprintf(stderr, C_RED "No such file or directory" C_RESET);
		return (1);
	}
	if (is_heredoc(minishell->cmd_node))
	{
		// printf("=============sequence===========\n");
		// fprintf(stderr, C_BLUE "sequence\n" C_RESET);
		return (sequential_executor(minishell));
	}
	else
	{
		pipex = update_pipe_fds(&minishell->cmd_node);
		minishell->pipex = &pipex;
		// fprintf(stderr, C_BLUE "parallel\n" C_RESET);
		return (parallel_executor(minishell));
	}
}

#include "minishell.h"
#include <signal.h>

void	ft_newline(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	is_command_in_every_pipe(t_cmd **cmd_node)
{
	t_cmd	*head;

	head = *cmd_node;
	while (head)
	{
		if (head->cmd_full[0] == NULL)
			head->exit_status = 127;
		head = head->next;
	}
}

void	print_env_sorted(char **env, int env_len);

void	free_minishell(t_minishell *minishell)
{
	free_tokens(minishell->token);
	free_cmd_nodes(&minishell->cmd_node);
}

int	is_only_spaces(char *line)
{
	int	i;

	i = 0;
	if (!*line)
		return (1);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n'
			&& line[i] != '\v' && line[i] != '\f' && line[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}

char	**ft_dup_env(char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

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
		// print_tokens(minishell->token);
		is_command_in_every_pipe(&minishell->cmd_node);
		first_last_cmd(&(minishell->cmd_node));
		minishell->exit_status = executor(minishell);
		// print_t_cmd(minishell->cmd_node);
		// // fprintf(stderr, C_GREEN "final_exit_status = %d\n" C_RESET, minishell->exit_status);
		free(line);
		// printf("pid = %d\n", getpid());

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
