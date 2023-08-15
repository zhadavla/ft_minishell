#include "../includes/minishell.h"

int	is_in_quotes(t_token *head)
{
	return ((head->quote == IN_QUOTE1 && head->next->quote == IN_QUOTE1)
		|| (head->quote == IN_QUOTE2 && head->next->quote == IN_QUOTE2));
}

/**
 * Merge env variables with words in quotes
 * also update len of token
 * it should also free the old token
 *
 */
void	concate_quotes(t_token **token)
{
	t_token	*head;
	t_token	*tmp;
	t_token	*prev;

	head = *token;
	while (head)
	{
		if (is_in_quotes(head))
		{
			tmp = head;
			while (tmp->next && tmp->next->quote == head->quote)
			{
				head->text = ft_strjoin(head->text, tmp->next->text);
				head->len += tmp->next->len;
				prev = tmp;
				tmp = tmp->next;
				if (prev != head)
					free_token(prev);
			}
			head->next = tmp->next;
			free_token(tmp);
			head->type = WORD;
		}
		head = head->next;
	}
}
