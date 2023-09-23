// #include "../includes/minishell.h"

// char *e_quote_to_str(t_quote quote)
// {
// 	if (quote == QUOTE0)
// 		return ("QUOTE0");
// 	if (quote == IN_QUOTE1)
// 		return ("IN_QUOTE1");
// 	if (quote == IN_QUOTE2)
// 		return ("IN_QUOTE2");
// 	return ("ERROR");
// }

// char *e_token_type_to_str(t_token_type type)
// {
// 	if (type == WORD)
// 		return ("WORD");
// 	if (type == PIPE)
// 		return ("PIPE");
// 	if (type == REDIR_IN)
// 		return ("REDIR_IN");
// 	if (type == REDIR_OUT)
// 		return ("REDIR_OUT");
// 	if (type == REDIR_APPEND)
// 		return ("REDIR_APPEND");
// 	if (type == ENV_VARIBLE)
// 		return ("ENV_VARIBLE");
// 	if (type == WHITE_SPACE)
// 		return ("WHITE_SPACE");
// 	if (type == HEREDOC)
// 		return ("HEREDOC");
// 	if (type == SINGLE_QUOTE)
// 		return ("SINGLE_QUOTE");
// 	if (type == DOUBLE_QUOTE)
// 		return ("DOUBLE_QUOTE");
// 	if (type == COMMAND)	
// 		return ("COMMAND");
// 	if (type == OUTFILE)
// 		return ("OUTFILE");
// 	if (type == OUTFILE_AP)
// 		return ("OUTFILE_AP");
// 	if (type == INFILE)
// 		return ("INFILE");
// 	if (type == DELIM_H)
// 		return ("DELIM_H");
// 	if (type == DOLLAR_SIGN)
// 		return ("DOLLAR_SIGN");
// 	if (type == BUILTIN)
// 		return ("BUILTIN");
// 	return ("ERROR");
// }

// // void print_qoute_status(t_quote q_s)
// // {
// // 	if (q_s == QUOTE0)
// // 		// fprintf(stderr, "QUOTE0\n");
// // 	else if (q_s == IN_QUOTE1)
// // 		// fprintf(stderr, "IN_QUOTE1\n");
// // 	else if (q_s == IN_QUOTE2)
// // 		// fprintf(stderr, "IN_QUOTE2\n");
// // }

// void print_tokens(t_token *head)
// {
//     // fprintf(stderr, "--------------------------------------------------------------------------------------------\n");
//     // fprintf(stderr, "|            content                          |    len   |      type      |     quote      |\n");
//     // fprintf(stderr, "--------------------------------------------------------------------------------------------\n");

//     while (head)
//     {
// 		// if (head->len > 1)
//         // fprintf(stderr, "|{%s}%*s|  %6zu  |  %12s  |  %12s  |\n",
//                head->text, (int)(45 - (head->len + 2)), "", head->len, e_token_type_to_str(head->type), e_quote_to_str(head->quote));
// 		// fprintf(stderr, "--------------------------------------------------------------------------------------------\n");
//         head = head->next;
//     }
// }

// void print_array_of_chars(char **array)
// {
// 	int i;

// 	i = 0;
// 	while (array[i])
// 	{
// 		// fprintf(stderr, "%s\n", array[i]);
// 		i++;
// 	}
// }

// void	print_t_cmd(t_cmd *head)
// {
// 	int	number_of_pipe;

// 	number_of_pipe = 0;
// 	while (head)
// 	{
// 		// // fprintf(stderr, "\n\n==================print_t_cmd=================\n\n");
// 		// fprintf(stderr, "\n==================pipe number [%d]=================\n",
// 			// number_of_pipe);
// 		// fprintf(stderr, "infile name: %s\n", head->infile_name);
// 		// fprintf(stderr, "infile_fd: %d\n", head->infile_fd);
// 		// fprintf(stderr, "outfile name: %s\n", head->outfile_name);
// 		// fprintf(stderr, "outfile_fd: %d\n", head->outfile_fd);
// 		if (head->is_heredoc)
// 		{
// 			// fprintf(stderr, "is_heredoc: %d\n", head->is_heredoc);
// 			// fprintf(stderr, "delim: %s\n", head->delim);
// 		}
// 		else
// 		{
// 			// fprintf(stderr, "is_before_heredoc: %d\n", head->is_before_heredoc);
// 			// fprintf(stderr, "is_after_heredoc: %d\n", head->is_after_heredoc);
// 			// for (int i = 0; head->cmd_full[i] != NULL; i++)
// 			// 	// fprintf(stderr, "cmd_full[%d]: %s\n", i, head->cmd_full[i]);
// 			// // fprintf(stderr, "\ninfile_names list\n\n");
// 			// for (int i = 0; head->infile_names[i] != NULL; i++)
// 			// 	// fprintf(stderr, "infile_names[%d]: %s\n", i, head->infile_names[i]);
// 			// // fprintf(stderr, "\noutfile_names list\n\n");
// 			// for (int i = 0; head->outfile_names[i] != NULL; i++)
// 				// fprintf(stderr, "outfile_names[%d]: %s\n", i, head->outfile_names[i]);
// 			// fprintf(stderr, "is_append: %d\n", head->is_append);
// 		}
// 		// fprintf(stderr, "is_first: %d\n", head->is_first);
// 		// fprintf(stderr, "is_last: %d\n", head->is_last);
// 		// fprintf(stderr, "exit_status: %d\n", head->exit_status);
// 		number_of_pipe++;
// 		head = head->next;
// 	}
// 	// fprintf(stderr, "\n");
// }

// void error_msg(char *msg)
// {
// 	// fprintf(stderr, "%s%s%s\n", C_RED, msg, C_RESET);
// }

// void blue_msg(char *msg)
// {
// 	// fprintf(stderr, "%s%s%s\n", C_BLUE, msg, C_RESET);
// }

// void green_msg(char *msg)
// {
// 	// fprintf(stderr, "%s%s%s\n", C_GREEN, msg, C_RESET);
// }

// void yellow_msg(char *msg)
// {
// 	// fprintf(stderr, "%s%s%s\n", C_YELLOW, msg, C_RESET);
// }
