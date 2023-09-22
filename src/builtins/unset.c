#include "../../includes/minishell.h"

void remove_env_node(t_env *env_head, t_env *to_remove)
{
	t_env *tmp;
	t_env *prev;

	tmp = env_head;
	prev = NULL;
	while (tmp)
	{
		if (tmp == to_remove)
		{
			if (prev)
				prev->next = tmp->next;
			else
				env_head = tmp->next;
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int ft_unset(t_minishell *minishell)
{
	t_cmd	*cmd_node = minishell->cmd_node;
	char	*key = NULL;
	t_env	*tmp;
	t_env	*prev;

	if (!cmd_node->cmd_full[1])
	{
		fprintf(stderr, C_RED "unset: here should be an error message\n" C_RESET);
		return (0);
	}
	minishell->env_list = create_env_copy(minishell->env);
	tmp = minishell->env_list;
	prev = NULL;
	key = cmd_node->cmd_full[1];
	while (tmp)
	{
		if (!ft_strncmp(key, tmp->full_env, ft_strlen(key)))
		{
			remove_env_node(minishell->env_list, tmp);
			break ;
		}
		prev = tmp;
		fprintf(stderr, C_YELLOW "%s\n" C_RESET, tmp->full_env);
		tmp = tmp->next;
	}
	minishell->env = t_env_to_array(minishell->env_list);
		// fprintf(stderr, C_YELLOW "ft_unset\n" C_RESET);
	free_env(minishell->env_list);
	return (0);
}