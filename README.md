# ft_minishell

# Part I: The Parser

Goal: *Get a populated linked list with one node per cmd/pipe. Each node will contain all the necessary information to be able to execute the commands in Part II.*

## Steps: 
- [ ] 1. Read a string in a prompt using **readline**.
- [x] 2. **Split** the string by space, single and double quotes resulting in char **.
      	- [x] Tokenize every element by categories (word, double_quote, singe_quote, pipe, redirection flag, whitespace, special characters, outfile, infile, outfile_ap, command etc.)
	- [x] Create a linked list, one node will have the content, len, token_type and q_s.
	- [x] Delete nodes with the whitespace OUTSIDE of the quotes;
	- [x] Concatenate by groups (commands, redirections, $VAR); 
- [x] 3. Expand environmental variable with a dollar sigh **$VAR**.
	- [x] concatinate $ sign with the words after till we meet whitespace (it happens after expansion);
- [x] 4. Expand a wave sign **~** to the user's home directory.
- [x] 5. Handle **pipes**:
   	- [x]  define amount of cmds
   	- [x] remove pipe sign **|** from the string array. 
- [x] 6. Handle **redirections**:
	 - [x] < input 
	 - [x] \> output 
	 - [x] \>> append to output
- [ ] 7. Handle **heredoc**.
	- [ ] the position of heredoc sign in the string (before, in the middle of the pipes, or in the end).
- [x] 8. Tokenize commands (change WORD token type to COMMAND token type)
	- [x] command in QUOTES will be executed as a command only if there is nothing else in the quotes; if there is something else, it will be treated as a string;
- [x] 9. Fill in each node in ```C struct s_cmd_node ``` in the linked list.
- [ ] 10. Finish handling error messages for invalid input.

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
- [x] **Step 3:** Single quotes do not expand environmental variables (e.g. echo '$USER' will print $USER).
- [x] **Step 3:** Single and double quotes do not expand wave sign ~ to the user's home directory. (e.g. echo "~/src" will print ~/src).
- [ ] Spaces and tabs WITHOUT QUOTES will be printed as ONE space between elements.
- [ ] readline promt: if the line returned contains only spaces and tabs → all you need to do is to display a new prompt, if there is something in the line then you’ll add it to your history.
- [x] **Step 9:** commands can be executed in single and double quotes when first in pipe; 

# Part 2: The Executer

- [ ] handle $? --> this will be handled in Part II.


# Status as of 24.08 (what is left):

- [ ] built ins
- [ ] $?
- [ ] error handling (also with $?)
- [ ] signals
- [ ] readline (or get next line) to be decided what is better to use :)
- [ ] heredoc -> on execute command stage :(
- [ ] multiple heredocs handling :(((
- [ ] history
