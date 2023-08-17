#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include <stdbool.h>

# define TRUE 1
# define FALSE 0

enum					e_token_type
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
	COMMAND,
	OUTFILE,
	OUTFILE_AP,
	INFILE
};

enum					e_quote
{
	IN_QUOTE1 = '\'',
	IN_QUOTE2 = '\"',
	QUOTE0 = 0,
};

typedef struct s_cmd
{
	char				*infile_name;
	char				*outfile_name;
	int					infile_fd;
	int					outfile_fd;
	char				**cmd_full;
	char				**env;
	char				*cmd_path;
	struct s_cmd 				*next;
}						t_cmd;

typedef struct token
{
	enum e_token_type	type;
	enum e_quote		quote;
	char				*text;
	size_t				len;
	struct token		*next;
}						t_token;

int is_pipe(char c);
void					t_cmd_add(t_cmd **head, t_cmd *new);
int						is_unclosed_quotes(t_token **token);
void					print_tokens(t_token *head);
t_token					*apply_lexer(char *str);
void					free_tokens(t_token *head);
void					free_token(t_token *token);
enum e_token_type		update_token_type(char c, char d);
t_token					*new_token(char *text, size_t len,
							enum e_token_type type, enum e_quote quote);
enum e_quote			update_q_s(char c, enum e_quote quote);
enum e_token_type		update_token_type(char c, char d);
void					merge_envs(t_token **token);
char					**create_full_command(t_token *token);
char					*get_env_value(char *text, char **env);
void					expand_env(t_token **token, char **env);
void					concate_quotes(t_token **token);
void					concate_redirections_heredoc(t_token **token);
void					validate_commands(t_token **token, char **g_env);
void					remove_whitespaces(t_token **token);
void					validate_filename(t_token **token);

#endif // MINISHELL_H
