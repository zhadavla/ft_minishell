#include "../includes/minishell.h"

t_token	*new_token(char *text, size_t len, enum e_token_type type, enum e_quote quote)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->text = text;
	new->len = len;
	new->type = type;
	new->quote = quote;
	new->next = NULL;
	return (new);
}

void	free_token(t_token *token)
{
	free(token->text);
	free(token);
}

void	free_tokens(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free_token(tmp);
	}
}

int	is_special_character(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '\'' || c == '\"'
		|| c == '$' || c == ' ');
}

// change quote status if quote is opened or closed
enum e_quote	update_quote_status(char c, enum e_quote quote, int *i)
{
	if ((c == '\'' && quote == QUOTE1) || (c == '\"' && quote == QUOTE2))
	{
		// *i += 1;
		return (QUOTE0);
	}
	else if (c == '\'' && quote == QUOTE0)
	{
		// *i += 1;
		return (QUOTE1);
	}
	else if (c == '\"' && quote == QUOTE0)
	{
		// *i += 1;
		return (QUOTE2);
	}
	return (QUOTE0);
}

enum e_token_type update_token_type(char c, char d)
{
	
	if (c == '|')
		return (PIPE);
	if (c == '<' && d != '<')
		return (REDIR_IN);
	if (c == '>' && d != '>')
	{
	
		return (REDIR_OUT);
	}
	if (c == '>' && d == '>')
	{
	
		return (REDIR_APPEND);
	}
	if (c == '<' && d == '<')
		return (HEREDOC);
	if (c == '\'')
		return (SINGLE_QUOTE);
	if (c == '\"')
		return (DOUBLE_QUOTE);
	if (c == '$')
		return (ENV_VARIBLE);
	if (c == ' ')
		return (WHITE_SPACE);
	return (WORD);
}

void print_qoute_status(enum e_quote quote_status)
{
	if (quote_status == QUOTE0)
		printf("QUOTE0\n");
	else if (quote_status == QUOTE1)
		printf("QUOTE1\n");
	else if (quote_status == QUOTE2)
		printf("QUOTE2\n");
}

t_token *token_add_front(t_token *head, t_token *new)
{
	new->next = head;
	return (new);
}

t_token *token_add_back(t_token *head, t_token *new)
{
	t_token *tmp;

	if (!head)
		return (new);
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (head);
}

char *e_token_type_to_str(enum e_token_type type)
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
	return ("ERROR");
}



t_token	*apply_lexer(char *str)
{
	printf("str = {%s}\n", str);
	t_token *head  = NULL;

	int len = 0;
	int i = 0;
	enum e_token_type token_type;
	enum e_quote quote_status = QUOTE0;

	while (str[i])
	{
		// if character is a special character, write whole word 
		// (text before the special character) to the token
		// simoultaneously, write special char to another token
		if (is_special_character(str[i]))
		{
			if (len > 0 )
			{
				token_type = 	WORD;
				// printf("str[i] = {%c}\n", str[i]);
				t_token *tmp = new_token(ft_substr(str, i - len, len), len, token_type, quote_status);
				head = token_add_back(head, tmp);
				// printf("word = {%s}\n", ft_substr(str, i - len, len));
			
			}
			if (str[i] == '\'' || str[i] == '\"')
			{
				quote_status = update_quote_status(str[i], quote_status, &i);
				// print_qoute_status(quote_status);
			}
			head = token_add_back(head, new_token(ft_substr(str, i, 1), 1, update_token_type(str[i], str[i + 1]), quote_status));
				len = 0;
			// printf("special char {%c}\n", str[i]);
		}
		else
			len++;
		i++;
	}

	return (head);
}

char *e_quote_to_str(enum e_quote quote)
{
	if (quote == QUOTE0)
		return ("QUOTE0");
	if (quote == QUOTE1)
		return ("QUOTE1");
	if (quote == QUOTE2)
		return ("QUOTE2");
	return ("ERROR");
}

#include <string.h>

void print_tokens(t_token *head)
{
    printf("----------------------------------------------------------------------------\n");
    printf("|            content           |    len   |      type      |     quote      |\n");
    printf("----------------------------------------------------------------------------\n");

    while (head)
    {
		// if (head->len > 1)
        printf("|{%s}%*s|  %6zu  |  %12s  |  %12s  |\n",
               head->text, (int)(30 - (head->len + 2)), "", head->len, e_token_type_to_str(head->type), e_quote_to_str(head->quote));
		printf("----------------------------------------------------------------------------\n");
        head = head->next;
    }
}

