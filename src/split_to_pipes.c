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

int is_pipe(char c)
{
	return (c == '|' || c == '\0');
}

/**
 * Creates a new node of t_cmd
 * with the neccessary data for execution of the process
 * 
*/
t_cmd *new_cmd(t_token *till_pipe)
{
	t_cmd *node_cmd;

	node_cmd = malloc(sizeof(t_cmd));
	while (till_pipe)
	{
		create_full_command(&till_pipe, &node_cmd);
		till_pipe = till_pipe->next;
	}
	return (node_cmd);
}
/**
 * Populates the node of t_cmd 
 * with the neccessary data for execution of the process
 * creates list of tokens before the pipe, named till_pipe
*/
t_cmd *split_to_pipes(t_token **token)
{
	t_token *head = *token;
	t_token *till_pipe = NULL;
	t_cmd *cmd_head = NULL;

	while (head)
	{
		if (is_pipe(head->type))
		{
			t_cmd_add(&cmd_head, new_cmd(till_pipe));
			till_pipe = NULL;
		}
		else
			t_add(&till_pipe, new_token(ft_strdup(head->text), \
			head->len, head->type, head->quote));
		head = head->next;
	}
}

void print_t_cmd(t_cmd *head)
{
	while (head)
	{
		printf("infile name: %s\n", head->infile_name);
		printf("outfile name: %s\n", head->outfile_name);
		for (int i = 0; head->cmd_full[i] != NULL; i++)
			printf("cmd_full[%d]: %s\n", i, head->cmd_full[i]);
		head = head->next;
	}
}

void free_cmd_node(t_cmd *cmd_node)
{
	free(cmd_node->infile_name);
	free(cmd_node->outfile_name);
	for (int i = 0; cmd_node->cmd_full[i] != NULL; i++)
		free(cmd_node->cmd_full[i]);
	free(cmd_node->cmd_full);
}