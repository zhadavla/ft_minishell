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

void	tokenizer_breakdown(t_token **head, t_minishell *minishell, int num)
{
	if (num == 1)
	{
		merge_envs(head);
		expand_env(head, minishell);
		concatenate_minus(head);
		concate_quotes(head);
		merge_redirections_heredoc(head);
		validate_absolute_path(head);
		validate_commands(minishell);
	}
	if (num == 2)
	{
		remove_quotes(head);
		concate_leftover_strings(head);
		remove_whitespaces(head);
		validate_filename(head);
	}
	if (num == 3)
	{
		validate_dollarsign(head);
		validate_commands_two(head);
		validate_builtins(head);
	}
}

int	tokenizer_one(t_token **head, t_minishell *minishell)
{
	tokenizer_breakdown(head, minishell, 1);
	if (!is_quote_error(head))
	{
		write(2, "syntax error near unexpected token `newline'1\n", 46);
		free_tokens(*head);
		minishell->exit_status = 2;
		return (0);
	}
	tokenizer_breakdown(head, minishell, 2);
	if (validate_heredoc(head, minishell))
		return (0);
	tokenizer_breakdown(head, minishell, 3);
	if ((*head)->type == WORD)
	{
		write(2, "syntax error near unexpected token `newline'2\n", 46);
		free_tokens(*head);
		minishell->exit_status = 127;
		return (0);
	}
	return (1);
}

void validate_builtin_without_output_command(t_minishell *minishell)
{
	t_cmd *cmd = minishell->cmd_node;
	
    
	if (cmd && is_builtin_without_output(cmd) && cmd->next == NULL){
		printf("????????????????????????????????????????????????????????????????????????????????????????\n");
		return;
	}
	minishell->is_builtin_wo_command = 1;	
}

t_cmd	*tokenizer(t_token *head, t_minishell *minishell)
{
	t_cmd	*cmd_node;
	t_cmd	*tmp;

	if (tokenizer_one(&head, minishell) == 0)
	{
		return (0);
	}
	cmd_node = split_to_pipes(&head);
	tmp = cmd_node;
	while (tmp)
	{
		if (!tmp->is_heredoc && !tmp->cmd_full[0])
		{
			ft_putstr_fd("Command not found\n", 2);
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



int	lexer_tokenizer(t_minishell **minishell, char *line)
{
	(*minishell)->token = lexer(line, *minishell);
	if (!(*minishell)->token)
	{
		free(line);
		return (0);
	}
	(*minishell)->cmd_node = tokenizer((*minishell)->token, *minishell);
	if (!(*minishell)->cmd_node)
	{
		free(line);
		return (0);
	}
	return (1);
}
