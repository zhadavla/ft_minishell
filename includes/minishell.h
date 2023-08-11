#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
enum e_token_type;

typedef struct token
{
	e_token_type	type;
	e_quote			quote;
	char			*text;
	size_t			len;
	t_token			*next;
}					t_token;

typedef struct s_cmd
{
	char			**cmd_full;
	char			*cmd_path;
	char			**env;
}					t_cmd;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	ENV_VARIBLE,
	WHITE_SPACE,
	HEREDOC,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
}					e_token_type;

typedef enum e_quote
{
	QUOTE1 = '\'',
	QUOTE2 = '\"',
	QUOTE0 = 0,
}					e_quote;

/*******************PART I parser**********************/
/**
 * Splits the string {s} using the space ' ' as a delimiter.
 * Doesn't metter how many spaces are in {s}.
 * If there is unclosed quote, returns NULL.
 */
char				**split(char *str);
int					get_num_of_elems(char *str);

#endif // MINISHELL_H
