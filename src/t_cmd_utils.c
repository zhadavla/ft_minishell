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