#include 		"../includes/minishell.h"
/**
 * Counting parameters of command
*/
int count_parameters(t_token *token)
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
				// printf("count = %d\n", count);
				return (count);
			}
		else if (is_command && token->type == WORD)
			count++;
		token = token->next;
	}
	// printf("count = %d\n", count);
	return (count);
}


char **create_full_command(t_token **token)
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
		else if (is_command && ((*token)->type == PIPE || (*token)->type == REDIR_OUT || (*token)->type == REDIR_IN 
			|| (*token)->type == REDIR_APPEND || (*token)->type == HEREDOC))
			break;
		else if (is_command && ((*token)->type == WORD || (*token)->type == ENV_VARIBLE))
		{
			// printf("token->text = %s\n", (*token)->text);
			full_command[i] = ft_strdup((*token)->text);
			i++;
		}
		prev = *token;
		*token = (*token)->next;
		free_token(prev);	
	}
	full_command[i] = NULL;
	return (full_command);
}
	