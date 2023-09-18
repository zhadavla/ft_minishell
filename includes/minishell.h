/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:14:43 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/17 20:40:34 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include <fcntl.h>
# include <readline/readline.h>
# include <stdint.h>
# include <sys/wait.h>

# define TRUE 1
# define FALSE 0

typedef enum e_token_type	t_token_type;
typedef enum e_quote		t_quote;
typedef struct s_cmd		t_cmd;
typedef struct token		t_token;
typedef struct s_pipex		t_pipex;

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
	BUILTIN,
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
	NO_FILE_EXISTS = 1,  // bash: file: No such file or directory
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
	/*
		* full command with arguments, first element is command name
		*/
	char					**cmd_full;
	char					**env;
	char					*cmd_path;
	int						is_before_heredoc;
	int						is_after_heredoc;
	int						is_last;
	int						is_first;
	int						is_builtin;
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

typedef struct s_pipex
{
	int						fd_pipes_count;
	int						cmd_count;
	int						*fd_pipes;
	int						fd_ind;
}							t_pipex;

typedef struct s_env
{
	char 					*full_env;
	struct s_env			*next;
}							t_env;

#define C_RED "\x1b[31m"
#define C_GREEN "\x1b[32m"
#define C_YELLOW "\x1b[33m"
#define C_BLUE "\x1b[34m"
#define C_RESET "\x1b[0m"

void yellow_msg(char *msg);
void green_msg(char *msg);
void blue_msg(char *msg);
/**
 * means red
*/
void error_msg(char *msg);


/*******************int utilits for more readable code********************/
int							is_outfile(t_token *token);
int							is_infile(t_token *token);
int							is_file(t_token *token);
int							is_unclosed_quotes(t_token **token);
int							is_special_character(char c);
int							is_in_quotes(t_token *head);
/**
 * Compare length of env variable and text
 */
int							is_length_match(char *env_i, char *text);
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

void						print_array_of_chars(char **array);
void						remove_node(t_token **token, t_token *node);
void						remove_node_cmd(t_cmd **token, t_cmd *node);
void						remove_redirections(t_token **token);
void						command_to_words(t_token **token);
t_cmd						*find_heredoc_node(t_cmd **cmd_node);
t_cmd						*new_cmd(t_token *till_pipe);
void						print_t_cmd(t_cmd *head);
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
void						concatenate_minus(t_token **token);
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

void						open_files(t_cmd **cmd_node);

/**************************Pipes*******************************/

void						first_last_cmd(t_cmd **cmd_node);
t_pipex						update_pipe_fds(t_cmd **cmd_node, char **env);

char						**get_binaries(char **env);
void						execute_command(t_pipex *pipex, t_cmd *node_cmd,
								char **env, t_env *env_list);
void						parallel_executor(t_pipex pipex, t_cmd **cmd_node,
								char **env, t_env *env_list);
void						sequential_executor(t_cmd *node_cmd, char **env, t_env *env_list);

/**************************Executor*******************************/

void						free_split(char **strs);
char						*ft_join(char const *s1, char const *s2);
void						close_fd(t_pipex *pipex);

int							ft_dup2(int fd1, int fd2);
int							ft_execute(char **full_cmd, char **env);
/**
 * check if there is a heredoc in the command line
 */
int							is_heredoc(t_cmd *cmd);

int							is_pipe(t_token *token);
int							is_redirection_in(t_token *token);
int							is_redirection_out(t_token *token);

/**************************Builtins*******************************/
void						validate_builtins(t_token **token);
void						ft_echo(char **cmd_full);
void						ft_execute_builtin(t_cmd *cmd_node, char **env, t_env *env_list);
t_env						*create_env_copy(char **env);
void						validate_absolute_path(t_token **token);
char						**t_env_to_array(t_env *env);
void add_env_variable(t_env **env_list, char *env_text);
void	ft_export(char **commands, char **env, t_env *env_list);
#endif // MINISHELL_H
