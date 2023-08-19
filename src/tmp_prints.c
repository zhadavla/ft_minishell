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
