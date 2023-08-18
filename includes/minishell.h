/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:14:43 by vzhadan           #+#    #+#             */
/*   Updated: 2023/08/18 17:25:06 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include <stdbool.h>

# define TRUE 1
# define FALSE 0

typedef enum e_token_type	t_token_type;
typedef enum e_quote		t_quote;

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
	COMMAND,
	OUTFILE,
	OUTFILE_AP,
	INFILE
}							t_token_type;

typedef enum e_quote
{
	IN_QUOTE1 = '\'',
	IN_QUOTE2 = '\"',
	QUOTE0 = 0,
}							t_quote;

typedef struct s_cmd
{
	int						is_heredoc;
	int						is_append;
	char					*infile_name;
	char					*outfile_name;
	int						infile_fd;
	int						outfile_fd;
	char					**cmd_full;
	char					**env;
	char					*cmd_path;
	struct s_cmd			*next;
}							t_cmd;

typedef struct token
{
	t_token_type			type;
	t_quote					quote;
	char					*text;
	size_t					len;
	struct token			*next;
}							t_token;


void 						init_cmd_node(t_cmd **cmd_node);
int							is_pipe(char c);
void						t_cmd_add(t_cmd **head, t_cmd *new);
void free_cmd_node(t_cmd *cmd_node);
int							is_unclosed_quotes(t_token **token);
void						print_tokens(t_token *head);
t_token						*apply_lexer(char *str);
void						free_tokens(t_token *head);
void						free_token(t_token *token);
t_token_type				update_token_type(char c, char d);
t_token						*new_token(char *text, size_t len,
								t_token_type type, t_quote quote);
t_quote						update_q_s(char c, t_quote quote);
t_token_type				update_token_type(char c, char d);
void						merge_envs(t_token **token);
void						print_t_cmd(t_cmd *head);
/**
 * Creates full command for one pipe
 * writes redirections to the cmd_node
 */
/**
 * Populates the node of t_cmd
 * with the neccessary data for execution of the process
 * creates list of tokens before the pipe, named till_pipe
 */
t_cmd						*split_to_pipes(t_token **token);
void	t_add(t_token **head, t_token *new);
void						create_full_command(t_token **token,
								t_cmd **cmd_node);
char						*get_env_value(char *text, char **env);
void						expand_env(t_token **token, char **env);
void						concate_quotes(t_token **token);
void						concate_redirections_heredoc(t_token **token);
void						validate_commands(t_token **token, char **g_env);
void						remove_whitespaces(t_token **token);
void						validate_filename(t_token **token);
int							is_special_character(char c);
void						concate_leftover_strings(t_token **token);

#endif // MINISHELL_H
