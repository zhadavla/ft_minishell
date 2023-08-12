#include "../includes/minishell.h"

t_token	*new_token(char *text, size_t len, enum e_token_type type, enum e_quote quote)
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
enum e_quote	update_quote_status(char c, enum e_quote quote, int *i)
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

enum e_token_type update_token_type(char c, char d, int *len)
{
	*len = 1;
	if (c == '|')
		return (PIPE);
	if (c == '<' && d != '<')
		return (REDIR_IN);
	if (c == '>' && d != '>')
	{
		*len = 2;	
		return (REDIR_OUT);
	}
	if (c == '>' && d == '>')
	{
		*len = 2;
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

// t_token	*apply_lexer(char *str)
// {
// 	printf("str = {%s}\n", str);
// 	t_token *head;
// 	int len = 0;
// 	int i = 0;

// 	enum e_quote quote_status = QUOTE0;
// 	enum e_token_type type = WORD;
// 	head = new_token(NULL, 0, WORD, QUOTE0);
// 	int j = 0;

// 	while (str[i])
// 	{
// 		if (is_special_character(str[i]))
// 		{
// 			// printf("str[%d] = {%c}\n", i, str[i]);
// 			// quote_status = update_quote_status(str[i], quote_status, &i);
// 			// type = update_token_type(str[i], str[i + 1], &len);
// 			// head->next = new_token(ft_substr(str, i, len + 1), len, WORD, quote_status);
// 			printf("%s\n", ft_substr(str, i - len, len));
// 			printf("len = %d, i = %d, j = %d\n", len, i, j);
// 			len = 0;
	
// 		}
// 		else
// 		{
// 			len++;
// 		}
// 		i++;
// 	}

// 	return (head);
// }

t_token	*apply_lexer(char *str)
{
	printf("str = {%s}\n", str);
	t_token *head;
	int len = 0;
	int i = 0;

	while (str[i])
	{
		// if character is a special character, write whole word 
		// (text before the special character) to the token
		// simoultaneously, write special char to another token
		if (is_special_character(str[i ]))
		{
			if (len > 0)
			{
				printf("word = {%s}\n", ft_substr(str, i - len, len));
				len = 0;
			}
			printf("special char {%c}\n", str[i]);
		}
		else
			len++;
		i++;
	}

	return (head);
}


void print_tokens(t_token *head)
{
	while (head)
	{
		printf("text = %s\n", head->text);
		printf("len = %zu\n", head->len);
		printf("type = %d\n", head->type);
		printf("quote = %d\n", head->quote);
		printf("\n");
		head = head->next;
	}
}