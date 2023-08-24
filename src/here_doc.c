#include "../includes/minishell.h"


void	ft_putstr_fd(char *s, int fd);

void validate_heredoc(t_token **token)
{
	t_token *head;
	t_token *prev;

	head = *token;
	while (head)
	{
		if (head->type == HEREDOC)
		{
			if (head->next && head->next->type == WORD)
			{
				head->next->type = DELIM_H;
				if (!(head->next->next) || head->next->next->type != COMMAND)
				{
					free_tokens(head);
					ft_putstr_fd("Heredoc has to be followed by a command\n", 2);
					exit(SYNTAX_ERROR_NL);
				}
			}
			else
			{
				free_tokens(head);
				ft_putstr_fd("Delimeter has to be specified\n", 2);
				exit(SYNTAX_ERROR_NL);
			}
		}
		head = head->next;
	}
}