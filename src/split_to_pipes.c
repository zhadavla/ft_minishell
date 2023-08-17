// #include "../includes/minishell.h"

// /**
//  * Creates a new node of t_cmd
//  * with the neccessary data for execution of the process
//  * 
// */
// t_cmd *new_cmd(t_token *till_pipe)
// {
// 	t_cmd *node_cmd;

// 	node_cmd = malloc(sizeof(t_cmd));
// 	while (till_pipe)
// 	{
// 		node_cmd->cmd_full = create_full_command(&till_pipe);
// 		till_pipe = till_pipe->next;
// 	}
// 	return (node_cmd);
// }
// /**
//  * Populates the node of t_cmd 
//  * with the neccessary data for execution of the process
// */
// t_cmd *split_to_pipes(t_token **token)
// {
// 	t_token *head = token;
// 	t_token *till_pipe = NULL;
// 	t_cmd *cmd_head = NULL;

// 	while (head)
// 	{
// 		if (is_pipe(head->type))
// 		{
// 			t_cmd_add(&cmd_head, new_cmd(&till_pipe));
// 			till_pipe = NULL;
// 		}
// 		else
// 			t_add(&till_pipe, new_token(ft_strdup(head->text), head->type));
// 		head = head->next;
// 	}
// }