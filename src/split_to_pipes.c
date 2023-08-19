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
	create_full_command(&till_pipe, &node_cmd);
	return (node_cmd);
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
	return (cmd_head);
}

void	print_t_cmd(t_cmd *head)
{
	while (head)
	{
		printf("\n\nprint_t_cmd\n\n");
		printf("infile name: %s\n", head->infile_name);
		printf("outfile name: %s\n", head->outfile_name);
		for (int i = 0; head->cmd_full[i] != NULL; i++)
			printf("cmd_full[%d]: %s\n", i, head->cmd_full[i]);
		head = head->next;
	}
	printf("\n");
}
