# ft_minishell

# Part I: The Parser

Goal: *Get a populated linked list with one node per cmd/pipe. Each node will contain all the necessary information to be able to execute the commands in Part II.*

## Steps: 
1. Read a string in a prompt using **readline**.
2. **Split** the string by space, single and double quotes.
3. Expand environmental variable with a dollar sigh **$VAR**.
4. Expand a wave sign **~** to the user's home directory.
5. Handle pipes (count pipes, and extract from the char **).
6. Handle redirections ( < input, > output, >> append to output, << heredoc, 2> error output).
7. Fill in each node in ```C struct s_cmd_node ``` in the linked list.

Important Add-on: ***Handle errors, memory leaks and error outputs on each step we make.***

```C
typedef struct s_cmd_node
{
    int input_fd;
    int output_fd;
	  char	**cmd_full;
	  char	*cmd_path;
    char **env;
    t_cmd_node *next;
}		t_cmd_node;
```
