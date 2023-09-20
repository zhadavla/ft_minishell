#include "../../includes/minishell.h"

char *get_key(char *str)
{
	char *key;
	int i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	key = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] && str[i] != '=')
	{
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

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

void ft_unset(t_minishell *minishell)
{
	t_cmd	*cmd_node = minishell->cmd_node;
	char	**env = minishell->env;
	char	*key;
	t_env	*tmp;
	t_env	*prev;

	if (!cmd_node->cmd_full[1])
		return ;
	fprintf(stderr, C_YELLOW "ft_unset\n" C_RESET);
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
		tmp = tmp->next;
	}
	minishell->env = t_env_to_array(minishell->env_list);
}