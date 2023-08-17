# ft_minishell

# Part I: The Parser

Goal: *Get a populated linked list with one node per cmd/pipe. Each node will contain all the necessary information to be able to execute the commands in Part II.*

## Steps: 
- [ ] 1. Read a string in a prompt using **readline**.
- [x] 2. **Split** the string by space, single and double quotes resulting in char **.
- [x] 3. Expand environmental variable with a dollar sigh **$VAR**.
	- [ ] handle $?
- [x] 4. Expand a wave sign **~** to the user's home directory.
- [ ] 5. Handle **pipes**:
   	- [ ]  define amount of cmds
   	- [ ] remove pipe sign **|** from the string array. 
- [ ] 6. Handle **redirections**:
	 - [ ] < input 
	 - [ ] \> output 
	 - [ ] \>> append to output
	 - [ ]   << heredoc
	 - [ ]   2> error output (not mentioned in the subject)
- [ ] 7. Handle **heredoc**.
- [ ] 8. Tokenize commands (change WORD token type to COMMAND token type)
	- [ ] command in QUOTES will be executed as a command only if there is nothing else in the quotes; if there is something else, it will be treated as a string; 
- [ ] 9. Fill in each node in ```C struct s_cmd_node ``` in the linked list.

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
- **Step 3:** Single quotes do not expand environmental variables (e.g. echo '$USER' will print $USER).
- **Step 3:** Single and double quotes do not expand wave sign ~ to the user's home directory. (e.g. echo "~/src" will print ~/src).
- Spaces and tabs WITHOUT QUOTES will be printed as ONE space between elements.
- the position of >> sign in the string (before, in the middle of the pipes, or in the end).
- readline promt: if the line returned contains only spaces and tabs → all you need to do is to display a new prompt, if there is something in the line then you’ll add it to your history.
- **Step 9:** commands can be executed in single and double quotes when first in pipe; 

## Step 2 breakdown:
1. - [x] Tokenize every element by categories (word, double_quote, singe_quote, pipe, redirection flag, whitespace, special characters, outfile, infile, outfile_ap, command etc.)
2. - [x] Create a linked list, one node will have the content, len, token_type and q_s.
3. - [x] Delete nodes with the whitespace OUTSIDE of the quotes;
4. - [x] Concatenate by groups (commands, redirections, $VAR); 
   
