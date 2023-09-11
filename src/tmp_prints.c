#include "../includes/minishell.h"

char *e_quote_to_str(t_quote quote)
{
	if (quote == QUOTE0)
		return ("QUOTE0");
	if (quote == IN_QUOTE1)
		return ("IN_QUOTE1");
	if (quote == IN_QUOTE2)
		return ("IN_QUOTE2");
	return ("ERROR");
}

char *e_token_type_to_str(t_token_type type)
{
	if (type == WORD)
		return ("WORD");
	if (type == PIPE)
		return ("PIPE");
	if (type == REDIR_IN)
		return ("REDIR_IN");
	if (type == REDIR_OUT)
		return ("REDIR_OUT");
	if (type == REDIR_APPEND)
		return ("REDIR_APPEND");
	if (type == ENV_VARIBLE)
		return ("ENV_VARIBLE");
	if (type == WHITE_SPACE)
		return ("WHITE_SPACE");
	if (type == HEREDOC)
		return ("HEREDOC");
	if (type == SINGLE_QUOTE)
		return ("SINGLE_QUOTE");
	if (type == DOUBLE_QUOTE)
		return ("DOUBLE_QUOTE");
	if (type == COMMAND)	
		return ("COMMAND");
	if (type == OUTFILE)
		return ("OUTFILE");
	if (type == OUTFILE_AP)
		return ("OUTFILE_AP");
	if (type == INFILE)
		return ("INFILE");
	if (type == DELIM_H)
		return ("DELIM_H");
	if (type == DOLLAR_SIGN)
		return ("DOLLAR_SIGN");
	return ("ERROR");
}

void print_qoute_status(t_quote q_s)
{
	if (q_s == QUOTE0)
		printf("QUOTE0\n");
	else if (q_s == IN_QUOTE1)
		printf("IN_QUOTE1\n");
	else if (q_s == IN_QUOTE2)
		printf("IN_QUOTE2\n");
}

void print_tokens(t_token *head)
{
    printf("--------------------------------------------------------------------------------------------\n");
    printf("|            content                          |    len   |      type      |     quote      |\n");
    printf("--------------------------------------------------------------------------------------------\n");

    while (head)
    {
		// if (head->len > 1)
        printf("|{%s}%*s|  %6zu  |  %12s  |  %12s  |\n",
               head->text, (int)(45 - (head->len + 2)), "", head->len, e_token_type_to_str(head->type), e_quote_to_str(head->quote));
		printf("--------------------------------------------------------------------------------------------\n");
        head = head->next;
    }
}

void print_array_of_chars(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
}

void	print_t_cmd(t_cmd *head)
{
	int	number_of_pipe;

	number_of_pipe = 0;
	while (head)
	{
		// printf("\n\n==================print_t_cmd=================\n\n");
		printf("\n==================pipe number [%d]=================\n",
			number_of_pipe);
		printf("infile name: %s\n", head->infile_name);
		printf("infile_fd: %d\n", head->infile_fd);
		printf("outfile name: %s\n", head->outfile_name);
		printf("outfile_fd: %d\n", head->outfile_fd);
		if (head->is_heredoc)
		{
			printf("is_heredoc: %d\n", head->is_heredoc);
			printf("delim: %s\n", head->delim);
		}
		else
		{
			printf("is_before_heredoc: %d\n", head->is_before_heredoc);
			printf("is_after_heredoc: %d\n", head->is_after_heredoc);
			for (int i = 0; head->cmd_full[i] != NULL; i++)
				printf("cmd_full[%d]: %s\n", i, head->cmd_full[i]);
			printf("\ninfile_names list\n\n");
			for (int i = 0; head->infile_names[i] != NULL; i++)
				printf("infile_names[%d]: %s\n", i, head->infile_names[i]);
			printf("\noutfile_names list\n\n");
			for (int i = 0; head->outfile_names[i] != NULL; i++)
				printf("outfile_names[%d]: %s\n", i, head->outfile_names[i]);
			printf("is_append: %d\n", head->is_append);
		}
		printf("is_first: %d\n", head->is_first);
		printf("is_last: %d\n", head->is_last);
		number_of_pipe++;
		head = head->next;
	}
	printf("\n");
}
