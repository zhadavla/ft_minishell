#include "../includes/minishell.h"

static void	redirections_switch(t_token *token, t_cmd **cmd_node);
static int	count_parameters(t_token *token);

/**
 * Counting parameters of command
 */
static int	count_parameters(t_token *token)
{
	int	count;
	int	is_command;

	count = 0;
	is_command = FALSE;
	while (token)
	{
		if (token->type == COMMAND)
		{
			is_command = TRUE;
			count++;
		}
		else if (is_command && (token->type == PIPE || token->type == REDIR_OUT
				|| token->type == REDIR_IN || token->type == REDIR_APPEND
				|| token->type == HEREDOC))
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


int is_outfile(t_token *token)
{
	return (token->type == OUTFILE || token->type == OUTFILE_AP);
}

int is_infile(t_token *token)
{
	return (token->type == INFILE);
}

int is_file(t_token *token)
{
	return (is_outfile(token) || is_infile(token));
}

int count_files(t_token *token, int is_infile_flag)
{
	int	count;

	count = 0;
	while (token)
	{
		if (is_infile_flag && is_infile(token))
			count++;
		else if (!is_infile_flag && is_outfile(token))
			count++;
		token = token->next;
	}
	return (count);
}

/**
 * Writes to the cmd_node->infile_names all the infile names
*/
void get_infile_names(t_token *token, t_cmd **cmd_node)
{
	t_token	*tmp;
	t_token *prev;
	int		i;

	prev = NULL;
	i = count_files(token, TRUE);
	(*cmd_node)->infile_names = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	tmp = token;
	while (tmp)
	{
		if (is_infile(tmp))
		{
			prev = tmp;
			(*cmd_node)->infile_names[i] = ft_strdup(tmp->text);
			i++;
		}
		tmp = tmp->next;
	}
	(*cmd_node)->infile_names[i] = NULL;
	if (prev)
		(*cmd_node)->infile_name = ft_strdup(prev->text);
}

/**
 * Writes to the cmd_node the information about outfiles
 * also handles is_append flag by checking the last outfile node
*/
void get_outfile_names(t_token *token, t_cmd **cmd_node)
{
	t_token	*tmp;
	t_token	*prev;
	int		i;

	prev = NULL;
	i = count_files(token, FALSE);
	(*cmd_node)->outfile_names = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	tmp = token;
	while (tmp)
	{	
		if (is_outfile(tmp))
		{
			prev = tmp;
			(*cmd_node)->outfile_names[i] = ft_strdup(tmp->text);
			i++;
		}
		tmp = tmp->next;
	}
	(*cmd_node)->outfile_names[i] = NULL;
	if (prev && prev->type == REDIR_APPEND)
		(*cmd_node)->is_append = TRUE;
	if (prev)
		(*cmd_node)->outfile_name = ft_strdup(prev->text);
}

/**
 * Writes to the cmd_node the information about redirections
 * and removes the redirections from the list of tokens
 * cmd_node->infile_names, cmd_node->outfile_names,
 * cmd_node->is_append for the last outfile name
 */
void	handle_in_out_files(t_token **token, t_cmd **cmd_node)
{
	t_token	*tmp;
	
	remove_redirections(token);
	tmp = create_list_of_files(token);
	get_infile_names(tmp, cmd_node);
	get_outfile_names(tmp, cmd_node);
	free_tokens(tmp);
	printf("---------------------------------infile names:\n");
	print_array_of_chars((*cmd_node)->infile_names);
	printf("FINAL INFILE NAME: %s\n", (*cmd_node)->infile_name);
	printf("---------------------------------outfile names:\n");
	printf("FINAL OUTFILE NAME: %s\n", (*cmd_node)->outfile_name);
	print_array_of_chars((*cmd_node)->outfile_names);


}

void	create_full_command(t_token **token, t_cmd **cmd_node)
{
	char	**full_command;
	int		i;
	int		is_command;
	t_token	*prev;


	full_command = (char **)malloc(sizeof(char *) * (count_parameters(*token)
			+ 1));
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
		else if (is_command && ((*token)->type == WORD
				|| (*token)->type == ENV_VARIBLE))
		{
			full_command[i] = ft_strdup((*token)->text);
			i++;
		}
		prev = *token;
		*token = (*token)->next;
		free_token(prev);
	}
	full_command[i] = NULL;
	(*cmd_node)->cmd_full = full_command;
	(*cmd_node)->next = NULL;
}

void	init_cmd_node(t_cmd **cmd_node)
{
	*cmd_node = malloc(sizeof(t_cmd));
	(*cmd_node)->is_heredoc = FALSE;
	(*cmd_node)->is_append = FALSE;
	(*cmd_node)->infile_name = NULL;
	(*cmd_node)->infile_names = NULL;
	(*cmd_node)->outfile_names = NULL;
	(*cmd_node)->infile_fd = 0;
	(*cmd_node)->outfile_fd = 1;
	(*cmd_node)->cmd_full = NULL;
	(*cmd_node)->env = NULL;
	(*cmd_node)->cmd_path = NULL;
	(*cmd_node)->next = NULL;
}

