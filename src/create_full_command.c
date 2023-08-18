#include 		"../includes/minishell.h"

static void redirections_switch(t_token *token, t_cmd **cmd_node);
static int count_parameters(t_token *token);

/**
 * Counting parameters of command
*/
static int count_parameters(t_token *token)
{
	int count;
	int is_command;

	count = 0;
	is_command = FALSE;

	while (token)
	{	
		if (token->type == COMMAND)
		{
			is_command = TRUE;
			count ++;
		}
		else if (is_command && (token->type == PIPE || token->type == REDIR_OUT || token->type == REDIR_IN 
			|| token->type == REDIR_APPEND || token->type == HEREDOC))
			{
				is_command = FALSE;
				return (count);
			}
		else if (is_command && token->type == WORD)
			count++;
		token = token->next;
	}
	return (count);
}


void create_full_command(t_token **token, t_cmd **cmd_node)
{
	char **full_command;
	int i;
	int is_command;
	t_token *prev;

	full_command = (char **)malloc(sizeof(char *) * (count_parameters(*token) + 1));
	i = 0;
	is_command = FALSE;
	while (*token)
	{
		if ((*token)->type == COMMAND)
		{
			is_command = TRUE;
			full_command[i] = ft_strdup((*token)->text);
			i++;
		}
		else if (is_command && ((*token)->type == WORD || (*token)->type == ENV_VARIBLE))
		{	
			full_command[i] = ft_strdup((*token)->text);
			i++;
		}
		else if ((*token)->type == REDIR_APPEND || (*token)->type == REDIR_OUT || (*token)->type == REDIR_IN)
			redirections_switch(*token, cmd_node);
		prev = *token;
		*token = (*token)->next;
		free_token(prev);	
	}
	full_command[i] = NULL;
	(*cmd_node)->cmd_full = full_command;
	(*cmd_node)->next = NULL;
}

void init_cmd_node(t_cmd **cmd_node)
{
	*cmd_node = malloc(sizeof(t_cmd));
	(*cmd_node)->is_heredoc = FALSE;
	(*cmd_node)->is_append = FALSE;
	(*cmd_node)->infile_name = NULL;
	(*cmd_node)->outfile_name = NULL;
	(*cmd_node)->infile_fd = 0;
	(*cmd_node)->outfile_fd = 1;
	(*cmd_node)->cmd_full = NULL;
	(*cmd_node)->env = NULL;
	(*cmd_node)->cmd_path = NULL;
	(*cmd_node)->next = NULL;
}

static void redirections_switch(t_token *token, t_cmd **cmd_node)
{
	if (token->type == REDIR_OUT)
	{
		(*cmd_node)->outfile_name = ft_strdup(token->next->text);
		(*cmd_node)->is_append = FALSE;
	}
	else if (token->type == REDIR_APPEND)
	{

		(*cmd_node)->outfile_name = ft_strdup(token->next->text);
		(*cmd_node)->is_append = TRUE;
	}
	else if (token->type == REDIR_IN)
	{	
		(*cmd_node)->infile_name = ft_strdup(token->next->text);
	}
	else if (token->type == HEREDOC)
	{
		printf("<  {%s}\n", token->next->text);
		(*cmd_node)->infile_name = ft_strdup(token->next->text);
		(*cmd_node)->is_heredoc = TRUE;
	}
}