#include "../includes/minishell.h"

int is_unclosed_quotes(t_token **token)
{
	t_token *head;

	head = *token;
	while (head->next)
		head = head->next;
	return (head->quote == IN_QUOTE1 || head->quote == IN_QUOTE2);
}