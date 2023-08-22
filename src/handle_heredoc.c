#include "../includes/minishell.h"

void add_front_t_cmd(t_cmd **cmd_node, t_cmd *new)
{
    t_cmd	*tmp;

    if (!*cmd_node)
    {
        *cmd_node = new;
        return ;
    }
    tmp = *cmd_node;
    *cmd_node = new;
    (*cmd_node)->next = tmp;
}

void move_to_first_place_heredoc(t_cmd **cmd_node, t_cmd *node)
{
    t_cmd *tmp;

    tmp = node;
    // remove_node_cmd(cmd_node, node);
    // add_front_t_cmd(cmd_node, tmp);
}

void find_heredoc_node(t_cmd **cmd_node)
{
    t_cmd *head;

    head = *cmd_node;
    while (head)
    {
        if (head->is_heredoc)
            move_to_first_place_heredoc(cmd_node, head);
        head = head->next;
    }

}

void handle_heredoc(t_token **till_pipe, t_cmd **cmd_node)
{
    t_token *head;
    t_token *prev;

    head = *till_pipe;
    prev = NULL;
    while (head)
    {
        if (head->type == HEREDOC && head->next && head->next->type == DELIM_H)
        {
            (*cmd_node)->is_heredoc = TRUE;
            (*cmd_node)->delim = ft_strdup(head->next->text);
            prev = head;
			head = head->next;
			remove_node(till_pipe, prev);
            prev = head;
			head = head->next;
			remove_node(till_pipe, prev);
        }
        head = head->next;
    }
	/////////////////////////////////////////////////////////////
	printf("is_heredoc: %d\n", (*cmd_node)->is_heredoc);
	printf("Delimeter: %s\n", (*cmd_node)->delim);

}