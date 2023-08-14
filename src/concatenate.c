#include "../includes/minishell.h"

void free_between_tokens(t_token *head, t_token *tail)
{
	t_token *tmp;

	while (head != tail)
	{
		printf("freeing %s\n", head->text);
		tmp = head;
		head = head->next;
		free(tmp->text);
		free(tmp);
	}
}

/**
 * Merge env variables with words in quotes
 * also update len of token
 * it should also free the old token
 *
*/
void concate_quotes(t_token **token)
{
	t_token *head;
	t_token *tmp;
	t_token *prev;
	char *text;
	size_t len;

	head = *token;
	while (head)
	{
		if (head->quote == IN_QUOTE1 || head->quote == IN_QUOTE2)
		{
			tmp = head;
			text = head->text;
			len = head->len;
			while (tmp->next && tmp->next->quote == head->quote)
			{	
				text = ft_strjoin(text, tmp->next->text);
				len += tmp->next->len;
				t_token *prev = tmp;
				tmp = tmp->next;
				if (prev != head)
				free_token(prev);
			}
			head->text = text;
			head->len = len;
			head->next = tmp->next;
			free_token(tmp);
			head->type = WORD;
		}
		head = head->next;
	}
}

