/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:14:43 by vzhadan           #+#    #+#             */
/*   Updated: 2023/08/24 14:48:04 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include <stdbool.h>
# include <fcntl.h>

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
	INFILE,
	DELIM_H,
	DOLLAR_SIGN,
}							t_token_type;

typedef enum e_error_status
{
	SYNTAX_ERROR_NL = 2, // bash: syntax error near unexpected token `newline'
	NO_FILE_EXISTS = 1, //bash: file: No such file or directory
}							t_error_status;

typedef enum e_quote
{
	IN_QUOTE1 = '\'',
	IN_QUOTE2 = '\"',
	QUOTE0 = 0,
}							t_quote;

typedef struct s_cmd
{
	int						is_heredoc;
	char					*delim;
	int						is_append;
	char					**infile_names;
	char					*infile_name;
	char					**outfile_names;
	char					*outfile_name;
	int						infile_fd;
	int						outfile_fd;
	char					**cmd_full;
	char					**env;
	char					*cmd_path;
	int						is_before_heredoc;
	int						is_after_heredoc;
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

/*******************bool utilits for more readable code********************/
int							is_outfile(t_token *token);
int							is_infile(t_token *token);
int							is_file(t_token *token);
int							is_unclosed_quotes(t_token **token);
int							is_special_character(char c);
/**
 * Writes to the cmd_node the information about redirections
 * and removes the redirections from the list of tokens
 * cmd_node->infile_names, cmd_node->outfile_names,
 * cmd_node->is_append for the last outfile name
 */
void						handle_in_out_files(t_token **token,
								t_cmd **cmd_node);
void						handle_heredoc(t_token **till_pipe,
								t_cmd **cmd_node);
// void						find_heredoc_node(t_cmd **head);
void						print_array_of_chars(char **array);
void						remove_node(t_token **token, t_token *node);
void						remove_node_cmd(t_cmd **token, t_cmd *node);
void						remove_redirections(t_token **token);
void						command_to_words(t_token **token);
t_cmd						*find_heredoc_node(t_cmd **cmd_node);
t_cmd						*new_cmd(t_token *till_pipe);
void						move_to_first_place_heredoc(t_cmd **cmd_node);
// t_token						*create_list_of_files(t_token **till_pipe);

/**************************Tokenization*******************************/
void						validate_heredoc(t_token **token);
void						init_cmd_node(t_cmd **cmd_node);
void						free_cmd_node(t_cmd *cmd_node);
void						print_tokens(t_token *head);
t_token						*apply_lexer(char *str);
void						free_tokens(t_token *head);
void						free_token(t_token *token);
t_token_type				update_token_type(char c, char d);
t_token						*new_token(char *text, size_t len,
								t_token_type type, t_quote quote);
t_quote						update_q_s(char c, t_quote quote);
void						merge_envs(t_token **token);
void						print_t_cmd(t_cmd *head);
void						expand_env(t_token **token, char **env);
void						remove_whitespaces(t_token **token);
void						remove_quotes(t_token **token);
void						concate_leftover_strings(t_token **token);
void						validate_commands(t_token **token, char **g_env);
void						validate_commands_two(t_token **token);
void						validate_filename(t_token **token);
void						concate_quotes(t_token **token);
void						merge_redirections_heredoc(t_token **token);
void						validate_dollarsign(t_token **token);

/**************************Split to pipes*******************************/
/**
 * Populates the node of t_cmd
 * with the neccessary data for execution of the process
 * creates list of tokens before the pipe, named till_pipe
 */
t_cmd						*split_to_pipes(t_token **token);
void						t_add(t_token **head, t_token *new);
void						create_full_command(t_token **token,
								t_cmd **cmd_node);
void						free_cmd_nodes(t_cmd **head);

void    open_files(t_cmd **cmd_node);

#endif // MINISHELL_H
