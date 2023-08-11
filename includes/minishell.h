#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_printf.h"
# include "libft.h"
# include "get_next_line.h"

// typedef struct t_cmd_n
// {
// 	int 		input_fd;
// 	int 		output_fd;
// 	char		**cmd_full;
// 	char		*cmd_path;
// 	char 		**env;
// 	t_cmd_n 	*next;
// }		t_cmd_n;

/*******************PART I parser**********************/
/**
 * Splits the string {s} using the space ' ' as a delimiter.
 * Doesn't metter how many spaces are in {s}.
 * If there is unclosed quote, returns NULL.
*/
char **split(char *str);
int get_num_of_elems(char *str);


#endif // MINISHELL_H
