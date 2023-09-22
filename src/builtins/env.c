#include "../../includes/minishell.h"

void ft_env(t_minishell *minishell)
{
	t_cmd	*cmd_node = minishell->cmd_node;
	char	**env = minishell->env;
	int len = -1;
	while (env[++len])
	{
		printf("%s\n", env[len]);
		free(env[len]);
	}
	free(env);
}