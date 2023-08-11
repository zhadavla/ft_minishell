# ft_minishell

# Part I: The Parser

Goal: *Get a populated linked list with one node per cmd/pipe. Each node will contain all the necessary information to be able to execute the commands in Part II.*

## Steps: 
1. Read a string in a prompt using **readline**.
2. **Split** the string by space, single and double quotes resulting in char **.
3. Expand environmental variable with a dollar sigh **$VAR**.
4. Expand a wave sign **~** to the user's home directory.
5. Handle **pipes**:
   	- define amount of cmds;
   	- remove pipe sign **|** from the string array.
7. Handle **redirections**:
   	-  < input
	- \> output
	-  \>> append to output
	-  << heredoc
	-  2> error output
9. Handle **heredoc**.
11. Fill in each node in ```C struct s_cmd_node ``` in the linked list.

Important Add-on: ***Handle errors, memory leaks and error outputs on each step we make.***

```C
typedef struct s_cmd
{
    	int 	input_fd;
    	int 	output_fd;
	char	**cmd_full;
	char	*cmd_path;
    	char 	**env;
    	t_cmd 	*next;
}		t_cmd;
```
## Tricky parts:
- Single quotes do not expand environmental variables (e.g. echo '$USER' will print $USER).
- Single and double quotes do not expand wave sign ~ to the user's home directory. (e.g. echo "~/src" will print ~/src).
- Spaces and tabs WITHOUT QUOTES will be printed as ONE space between elements.
- the position of >> sign in the string (before, in the middle of the pipes, or in the end).
- readline promt: if the line returned contains only spaces and tabs → all you need to do is to display a new prompt, if there is something in the line then you’ll add it to your history.
