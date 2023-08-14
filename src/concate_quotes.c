#include "../includes/minishell.h"

/**
 * Merge env variables with words in quotes
 * also update len of token
*/
void concate_quotes(t_token **token)
{
	t_token *head;
	t_token *tmp;
	char *text;
	size_t len;

	head = *token;
	while (head)
	{
		if (head->quote == IN_QUOTE1 || head->quote == IN_QUOTE2)
		{
			tmp = head;
			text = ft_strdup(head->text);
			len = head->len;
			while (tmp->next && tmp->next->quote == head->quote)
			{
				text = ft_strjoin(text, tmp->next->text);
				len += tmp->next->len;
				tmp = tmp->next;
			}
			head->text = text;
			head->len = len;
			head->next = tmp->next;
			head->type = WORD;
		}
		head = head->next;
	}
}