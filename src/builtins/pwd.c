#include "../../includes/minishell.h"

void ft_pwd(t_minishell *minishell)
{
    char *cwd = getcwd(NULL, 0);
    t_cmd *cmd_node = minishell->cmd_node;

    if (cwd == NULL)
    {
        cmd_node->exit_status = 69;
        return;
    }
    printf("%s\n", cwd);
    // fprintf(stderr, C_RED "%s\n" C_RESET, cwd);
    free(cwd);
}