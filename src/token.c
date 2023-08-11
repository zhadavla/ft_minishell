#include "../includes/minishell.h"

t_token	*new_token(char *text, size_t len, e_token_type type, e_quote quote)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
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
e_quote	update_quote_status(char c, e_quote quote, int *i)
{
	if ((c == '\'' && quote == QUOTE1) || (c == '\"' && quote == QUOTE2))
	{
		*i += 1;
		return (QUOTE0);
	}
	else if (c == '\'' && quote == QUOTE0)
	{
		*i += 1;
		return (QUOTE1);
	}
	else if (c == '\"' && quote == QUOTE0)
	{
		*i += 1;
		return (QUOTE2);
	}
	return (QUOTE0);
}

e_token_type update_token_type(char c, char d)
{
	if (c == '|')
		return (PIPE);
	else if (c == '<' && d != '<')
		return (REDIR_IN);
	else if (c == '>' && d != '>')
		return (REDIR_OUT);
	else if (c == '>' && d == '>')
		return (REDIR_APPEND);
	else if (c == '<' && d == '<')
		return (HEREDOC);
	else if (c == '\'')
		return (SINGLE_QUOTE);
	else if (c == '\"')
		return (DOUBLE_QUOTE);
	else if (c == '$')
		return (ENV_VARIBLE);
	else if (c == ' ')
		return (WHITE_SPACE);
	else
		return (WORD);
}

t_token	*apply_lexer(char *str)
{
	t_token *head;
	size_t len = 0;
	int i = 0;
	bool is_dquote_open = false;
	bool is_squote_open = false;
	e_quote quote_status = QUOTE0;
	e_token_type type = WORD;

	while (str[i])
	{
		if (is_special_character(str[i]))
		{
			quote_status = update_quote_status(str[i], quote_status, &i);
			type = update_token_type(str[i], str[i + 1]);


			head = new_token(ft_substr(str, i, i + len), len, WORD, quote_status);


			len = 0;
		} 

		
		i++;
	}

	return (head);
}