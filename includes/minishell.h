#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_cmd
{
	int 		input_fd;
	int 		output_fd;
	char		**cmd_full;
	char		*cmd_path;
	char 		**env;
	t_cmd_node 	*next;
}		t_cmd_node;


# include "ft_printf.h"
# include "libft.h"
# include "get_next_line.h"

#endif // MINISHELL_H
