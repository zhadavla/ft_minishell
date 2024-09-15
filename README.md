# Minishell Project

## Overview

The **Minishell** project was developed as part of an academic requirement during August-September 2023, using the **C programming language**. The primary objective of this project was to create a simplified version of the **Bash shell** in **plain C**, implementing core shell functionalities such as command parsing, tokenizing input, executing commands, managing built-ins, handling signals, and managing multiple processes.

## Key Features and Components

### 1. **Bash Shell Clone in C**
Minishell replicates essential functionalities of the Bash shell. The project focuses on providing a shell environment capable of executing commands, managing built-in shell commands, handling pipelines, and controlling processes.

### 2. **Command Parsing and Tokenization**
The input commands are parsed and tokenized into executable segments, following the structure of standard command-line interfaces. This process involves breaking down the user input into commands and arguments, preparing them for execution.

### 3. **Execution of Programs**
The shell includes a robust executor responsible for running both built-in commands and external programs. It searches for the appropriate executables using the `PATH` environment variable or absolute/relative paths.

### 4. **Built-in Commands**
Minishell implements a set of core shell built-ins, mimicking Bash's behavior. These built-ins include:

- **export**: Manage environment variables.
- **env**: Display the environment.
- **exit**: Exit the shell.
- **unset**: Remove environment variables.
- **echo**: Print text to the terminal.
- **cd**: Change the current directory.
- **pwd**: Print the current directory.

The shell is designed to handle many edge-case behaviors, ensuring consistency with how Bash operates in various scenarios.

### 5. **Parallel Process Execution**
The shell supports the execution of multiple processes in parallel, allowing for efficient management of pipelines and concurrent commands. The `pipe()` system call is used to connect commands in a pipeline, directing the output of one command as the input to the next.

### 6. **Signal Handling**
Minishell implements signal handling to manage critical signals such as `SIGINT`, `EOF`, `SIGQUIT`, and `SIGTSTP`. The behavior is aligned with Bash shell conventions:

- **Ctrl+C (SIGINT)**: Interrupts the current process and displays a new prompt.
- **Ctrl+D (EOF)**: Exits the shell.
- **Ctrl+\\ (SIGQUIT)**: No specific behavior, ignored.
- **Ctrl+Z (SIGTSTP)**: Stops the process (backgrounding is not required in this implementation).

### 7. **Input and Output Redirection**
Minishell implements both input (`<`) and output (`>`, `>>`) redirection:

- **Input redirection (`<`)**: Redirects the input from a file instead of standard input.
- **Output redirection (`>`)**: Writes the command output to a file.
- **Append output (`>>`)**: Appends the output to a file without overwriting.
- **Here documents (`<<`)**: Reads input until a specified delimiter is encountered.

### 8. **Environment Variable Expansion**
The shell supports environment variable expansion, where variables prefixed by `$` are expanded to their corresponding values. For example, `$USER` expands to the current user’s name. The shell also handles the special variable `$?`, which expands to the exit status of the most recently executed command.

### 9. **Command History**
Minishell provides a working history feature, using the `readline` library to store and access previous commands. This enhances user experience by allowing them to recall and reuse past commands easily.

### 10. **Quote Handling**
Minishell properly handles single (`'`) and double (`"`) quotes in the command input:

- **Single quotes**: Prevents the shell from interpreting any special characters inside the quoted string.
- **Double quotes**: Prevents interpretation of special characters except for `$` (variable expansion).

## External Functions and Libraries Used

Minishell utilizes several external functions and system calls, including but not limited to:

- **Readline library**: Provides functionality for command line history and line editing.
- **Process management**: `fork()`, `execve()`, `wait()`, `waitpid()` for creating and managing child processes.
- **Signal handling**: `signal()`, `sigaction()` to manage various signals.
- **File and directory handling**: `open()`, `close()`, `read()`, `write()`, `getcwd()`, `chdir()`, `opendir()`, `readdir()`.
- **Environment management**: `getenv()`, `setenv()`, `unsetenv()`.
- **Redirection**: `dup()`, `dup2()`, `pipe()` to manage file descriptors and pipelines.

### Authorized Libraries
- **Libft**: A personal library for handling common C functionalities, authorized for use in this project.

## Key Challenges

1. **Signal Management**: Handling signals efficiently while avoiding global variables was a major challenge. The use of a single global variable to handle signals ensures the main data structures remain unaffected by signal interruptions.
   
2. **Edge-Case Handling for Built-ins**: Built-in commands such as `export` and `unset` required careful handling of edge cases, especially with environment variables and their memory management.

3. **Concurrency and Piping**: Implementing proper process synchronization when executing commands in parallel with pipes involved significant complexity. Ensuring seamless communication between processes was crucial for correct execution.

## Conclusion

The **Minishell** project is a fully functional, minimal shell built in plain C, capable of handling core shell functionalities similar to Bash. It was a comprehensive exercise in systems programming, focusing on process management, signal handling, file redirection, and command execution. Through this project, essential C programming skills and a deep understanding of Unix-based systems were honed, providing valuable experience in low-level systems development.
