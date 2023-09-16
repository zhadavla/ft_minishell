# ft_minishell

# Theory 

Environment variables and shell variables are both used to store and manage information in a Unix-like operating system's command-line environment. However, they serve different purposes and have some key distinctions:

### Environment Variables:

- Environment variables are variables that are available to all processes and applications running on the system, including those started by different users.
- They are typically set in the system's configuration files and are accessible by any program or script.
- Common environment variables include PATH (to specify directories to search for executable files), HOME (to indicate the user's home directory), and USER (to identify the currently logged-in user).
- Environment variables are usually written in uppercase letters, e.g., PATH=/usr/bin:/bin.

### Shell Variables:

- Shell variables are specific to the shell session in which they are defined. They are not visible or accessible to other processes or shell sessions.
- Users can create their own shell variables to store temporary data or customize their shell environment.
- Common shell variables include PS1 (to set the shell prompt), PS2 (the secondary prompt), and SHELL (to specify the default shell).
- Shell variables are typically written in uppercase letters as well, but they can be in lowercase too.


# I hope we'll not handle that: 
``` Bash
$ a=5
$ echo $a
5
$ bash
$ echo $a

$ export A=42
$ echo $A
42
$ bash 
$ echo $A
42

```
# WE DON'T HANDLE WHAT IS WRITTEN ABOVE.
export with no params will just print env, but in sorted way. 
# DEADLINE 24.09.2023

# Part I: The Parser

Goal: *Get a populated linked list with one node per cmd/pipe. Each node will contain all the necessary information to be able to execute the commands in Part II.*

## Steps:

- [x] 1. Read a string in a prompt using **readline**.
- [x] 2. **Split** the string by space, single and double quotes resulting in char **.
     
          - [x] Tokenize every element by categories (word, double_quote, singe_quote, pipe, redirection flag, whitespace, special characters, outfile, infile, outfile_ap, command etc.)
     - [x] Create a linked list, one node will have the content, len, token_type and q_s.
     - [x] Delete nodes with the whitespace OUTSIDE of the quotes;
     - [x] Concatenate by groups (commands, redirections, $VAR); 
- [x] 3. Expand environmental variable with a dollar sigh **$VAR**.
     - [x] concatinate $ sign with the words after till we meet whitespace (it happens after expansion);
- [x] 4. Expand a wave sign **~** to the user's home directory.
- [x] 5. Handle **pipes**:
     - [x] define amount of cmds
     - [x] remove pipe sign **|** from the string array. 
- [x] 6. Handle **redirections**:
     - [x] < input 
     - [x] \> output 
     - [x] \>> append to output
- [x] 7. Handle **heredoc**.
     - [x] the position of heredoc sign in the string (before, in the middle of the pipes, or in the end).
     - [x] invalid input: when there is a cat command with existing infile and heredoc: ``` cat <<heredoc Makefile ``` - handled as invalid input; 
- [x] 8. Tokenize commands (change WORD token type to COMMAND token type)
     - [x] command in QUOTES will be executed as a command only if there is nothing else in the quotes; if there is something else, it will be treated as a string;
- [x] 9. Fill in each node in ``` struct s_cmd_node ``` in the linked list.
- [ ] 10. Finish handling error messages for invalid input.

Important Add-on: ***Handle errors, memory leaks and error outputs on each step we make.***

```C
typedef struct s_cmd
{
        int     input_fd;
        int     output_fd;
    char    **cmd_full;
    char    *cmd_path;
        char     **env;
        t_cmd     *next;
}        t_cmd;
```

## Tricky parts:

- [x] **Step 3:** Single quotes do not expand environmental variables (e.g. echo '$USER' will print $USER).
- [x] **Step 3:** Single and double quotes do not expand wave sign ~ to the user's home directory. (e.g. echo "~/src" will print ~/src).
- [x] **Step 9:** commands can be executed in single and double quotes when first in pipe; 
- [ ] Spaces and tabs WITHOUT QUOTES will be printed as ONE space between elements.

# Part 2: The Executer

## Steps:
- [x] Pipe creation (split_to_pipes).
- [x] Creation of child processes and executing commands
- [x] handling FDs
- [x] Heredoc
- [x] Multiple heredocs
      - [x] In a situation when we have multiple heredocs, we will execute all the processes sequentially (not in parallel like in a pipex).
- [x] Sequential executor
- [x] Parallel executor

# Part 3: ADD-ONs

- [ ] built ins
- [ ] $?
- [ ] signals
- [ ] history

# Status as of 13.09 (what is left):

- [ ] built ins
- [ ] $?
- [ ] error handling for invalid input;
- [ ] error handling (also with $?);
- [ ] signals
- [x] readline
     - [ ] readline promt: if the line returned contains only spaces and tabs → all you need to do is to display a new prompt, if there is something in the line then you’ll add it to your history.
- [ ] history
- [ ] handle the paths and compiled programs as a COMMAND token, so execve can execute them.
     - e.g. ./minishell should be executed inside ./minishell with a path: /home/user/ft_minishell/minishell
     - or /bin/ls is also works in execve function and should be executed without errors.
     - we need to tokenize them first as the COMMAND, and then handle a the paths to pass to execve function.
     -  [x] /bin/ls is passed to the execve in this form: execve("/bin/ls", {"/bin/ls", NULL}, NULL);
     - ./minishell: execve("./minishell", {"./minishell", NULL}, NULL);
     - 
# DEADLINE 24.09.2023
