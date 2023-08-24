#include "../includes/minishell.h"

void	t_cmd_add(t_cmd **head, t_cmd *new)
{
	t_cmd	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	is_pipe(t_token *token)
{
	return (token->type == PIPE);
}

/**
 * Creates a new node of t_cmd
 * with the neccessary data for execution of the process
 *
 */
t_cmd	*new_cmd(t_token *till_pipe)
{
	t_cmd	*node_cmd;

	init_cmd_node(&node_cmd);
	handle_heredoc(&till_pipe, &node_cmd);
	// find_heredoc_node(&node_cmd);
	handle_in_out_files(&till_pipe, &node_cmd);
	command_to_words(&till_pipe);
	create_full_command(&till_pipe, &node_cmd);
	// printf({"{%d}"}, (*node_cmd).is_heredoc);
	// print_t_cmd(node_cmd);
	return (node_cmd);
}

int	is_redirection_in(t_token *token)
{
	return (token->type == REDIR_IN);
}

int	is_redirection_out(t_token *token)
{
	return (token->type == REDIR_OUT || token->type == REDIR_APPEND);
}

/**
 * Removes the node with redirections from the till_pipe list
 */
void	remove_redirections(t_token **till_pipe)
{
	t_token	*head;
	t_token	*prev;

	head = *till_pipe;
	prev = NULL;
	while (head)
	{
		if ((is_redirection_in(head) || is_redirection_out(head)))
		{
			prev = head;
			head = head->next;
			remove_node(till_pipe, prev);
		}
		head = head->next;
	}
}

/**
 * Populates the node of t_cmd
 * with the neccessary data for execution of the process
 * creates list of tokens before the pipe, named till_pipe
 */
t_cmd	*split_to_pipes(t_token **token)
{
	t_token	*head;
	t_token	*till_pipe;
	t_cmd	*cmd_head;
	t_cmd	*tmp_cmd;

	head = *token;
	till_pipe = NULL;
	cmd_head = NULL;
	while (head)
	{
		if (head->type == PIPE)
		{
			tmp_cmd = new_cmd(till_pipe);
			t_cmd_add(&cmd_head, tmp_cmd);
			till_pipe = NULL;
		}
		else
			t_add(&till_pipe, new_token(ft_strdup(head->text), head->len,
					head->type, head->quote));
		head = head->next;
	}
	tmp_cmd = new_cmd(till_pipe);
	t_cmd_add(&cmd_head, tmp_cmd);
	till_pipe = NULL;
	
	move_to_first_place_heredoc(&cmd_head);
	// t_cmd *tmp = find_heredoc_node(&cmd_head);
	// move_to_first_place_heredoc(&cmd_head, tmp);
	return (cmd_head);
}

void	print_t_cmd(t_cmd *head)
{
	int	number_of_pipe;

	number_of_pipe = 0;
	while (head)
	{
		// printf("\n\n==================print_t_cmd=================\n\n");
		printf("\n==================pipe number [%d]=================\n",
			number_of_pipe);
		printf("infile name: %s\n", head->infile_name);
		printf("infile_fd: %d\n", head->infile_fd);
		printf("outfile name: %s\n", head->outfile_name);
		printf("outfile_fd: %d\n", head->outfile_fd);
		if (head->is_heredoc)
		{
			printf("is_heredoc: %d\n", head->is_heredoc);
			printf("delim: %s\n", head->delim);
		}
		else
		{
			printf("is_before_heredoc: %d\n", head->is_before_heredoc);
			printf("is_after_heredoc: %d\n", head->is_after_heredoc);
			for (int i = 0; head->cmd_full[i] != NULL; i++)
				printf("cmd_full[%d]: %s\n", i, head->cmd_full[i]);
			printf("\ninfile_names list\n\n");
			for (int i = 0; head->infile_names[i] != NULL; i++)
				printf("infile_names[%d]: %s\n", i, head->infile_names[i]);
			printf("\noutfile_names list\n\n");
			for (int i = 0; head->outfile_names[i] != NULL; i++)
				printf("outfile_names[%d]: %s\n", i, head->outfile_names[i]);
			printf("is_append: %d\n", head->is_append);
		}
		number_of_pipe++;
		head = head->next;
	}
	printf("\n");
}
