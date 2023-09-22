#include <stdio.h>
#include <assert.h>

#include "../includes/minishell.h"

void test_parser_tokeniser(char **env)
{
	char *env_tests[] =
		{
			"grep $PWD file",
			"grep $PW D file",
			"grep $ PWD file",
			"grep $PWDG file",
			"grep $ file"};
	// char * tests[] = {
	// 	"grep \'PWD   fsg\' file",
	// 	"$HOME",
	// 	"$ f",
	// 	"~"
	// }; 	
	char *tests[] = {
		// "echo \"test", //unclosed quotes
		// "echo $TEST", // works
		// "echo \"df s\"", // +
		// "echo $USER", // +
		// ">$USER", // -
		// // "< $USER echo 5555", // -
		// // "echo < $USER 5555", // -
		// // "echo 555 < $USER", // -
		// // "> $USER echo 5555", // -
		// // "echo > $USER 5555", // -
		// // "echo 555 > $USER", // -
		// "echo '$TEST'", //+
		// "echo \"$HOME$TEST$USER\"", // +
		// "echo \"$TEST$TEST=lol$TEST\"",//+
		// "echo \"   $TEST lol $TEST\"", //+
		// "echo $TEST$TEST$TEST", //+
		// "echo $TEST$TEST=lol$TEST",
		// " test ",
		// " test",
		// "echo \"$=TEST\"",
		// "echo \'$=TEST\'",
		// "echo $=TEST",
		// "echo \"$\"",
		// "echo \"$1TEST\"",
		// "echo \"$T1TEST\"",
		// "echo $TEST$TEST$=TEST",
		// "echo ++ll",
		// "echo l++lld$fkl--sd+fl",
		// "echo \'l++lld$fkl--sd+fl\'",
		// "echo \"l++lld$fkl--sd+fl\"",
		// "echo l++lld$HOME--sd+fl",
		// "echo l++lld$fkl-- sd+fl >> outfile",
		// "echo l++lld$HOME -- sd+fl >> outfile",
		// "echo $HOME",
		// "echo ?TEST", //expected output: ?TEST
		// "echo \"$?TEST\"", //expected output: 0TEST (expanded variable + TEST)
		// "echo ?", //expected output: ?
		// "echo $?", //expected output: expanded variable
		// "echo \"$?\"", //expected output: expanded variable
		// "echo \'$?\'", //expected output: $?
		// "echo $USER",
		// ">outfile grep hello world",
		// "echo \"hello world\" | grep hello world",
		// "< infile grep hello world | > filecat cat -e | wc -l > outfile",
		// "<infile grep \"hello world\" > outfile",
		// "echo $TEST",
		// "echo \"df s\"",
		// "echo $USER",
		// "echo '$TEST'",
		// "echo \"$HOME$TEST$USER\"",
		// "echo \"$TEST$TEST=lol$TEST\"",
		// "echo \"   $TEST lol $TEST\"",
		// "echo $TEST$TEST$TEST",
		// "echo $TEST$TEST=lol$TEST",
		// "lol",
		// "echo    $TEST lol $TEST",
		// "echo test ",
		// " test ",
		// " test",
		// "echo \"$=TEST\"",
		// "echo \'$=TEST\'",
		// "echo $=TEST",
		// "echo \"$\"",
		// "echo \"$?TEST\"",
		// "echo \"$1TEST\"",
		// "echo \"$T1TEST\"",
		// "echo $TEST$TEST$=TEST",
		// "echo ++ll",
		// "echo ++lldsf+_sd?$fkl--sdfl"
		// // "env | sort | grep -v SHLVL | grep -v _=",
		// // "export | sort | grep -v SHLVL | grep -v _= | grep -v OLDPWD",
		// "grep -v -l",
		// "grep -vl",
		// "export =",
		// // "export 1TEST= ;\' $ENV_SHO", //unclosed quotes
		// // "export TEST ;' $EXPORT_SHO", //unclosed quotes
		// "export ",
		// "=",
		// "export TES=T=",
		// "export TE+S=T=",
		// "export TEST=LOL ; echo $TEST ;\' $ENV_SHO\'",
		// "export TEST=LlOL ; echo $TEST$TEST$TEST=lol$TEST",
		// "export TEST=LOL; export TEST+=LOL ; echo $TEST ; $ENV_SHO",
		// // "export TEST=\"ls       -l     - a\" ; echo $TEST ; $LS ; \' $ENV_SHO", //unclosed quotes
		// "echo test > ls cat ls",
		// "ls > file >>f1 <i1 < i2 cat | grep 42  >> o2 | < in1 wc -l > file2",
		// "echo test > ls",
		// "echo test > ls >> ls >> ls echo test >> ls cat ls", 
		// "echo test > ls1 >> ls2 >> ls3 echo test >> ls4 cat ls5",
		// "> lol echo test lol; cat lol",
		// ">lol echo > test>lol>test>>lol>test mdr >lol test >test; cat test",
		// "\'cat\' < \"ls\"",
		// "\'cat\' < \"filename\"",
		// "\'cat\' >> filname",
		// // "cat << ls > ls", //missing 2 frees validate_heredoc 
		// // "cat << ls >> ls",
		// "sdfsd < f1 < f2 < f3 > o1 | hello >> o2 >>o3 | sdfs <f4 >o5 sdfsdf",
		// "< if1 < if2 < if3 < if4 grep 42",
		// "< if1 < if2 < if3 < if4 > of1 >> of2 >> of3 > of4",
		// "echo \"hello world\"",
		// ">> ls | ls -l",
		// "< ls cat",
		// "<inifle1 < infile2 cat",
		// "< if1 grep ll | cat > outfile > fil3",
		// "< infile2 grep \"ls -la hello world\" | cat > outfile2",
		// "ls -l -a > out2 | echo hello >> out1 | wc -l",
		// "cat << stop ls",
		// "echo 42"
		// "<< stop cat",
		// "grep hello | wc -l | << stop cat",
		// "<< stop cat >outf | grep hello >>outf |  wc -l",
		// "<< stop tr '_' '*' | cat | << stop2 cat | wc -l",
		// "cat << stop",
		// "echo 42 | echo 42 | wc -l",
		// "echo 42 | grep 42 > cat | << stop cat"
		// "<<",
		// "echo 42 > out | grep 42",
		// "> test000",
		// "ls",
		// "echo hello | ls | cat | ls | ls -l | echo 42",
		// "echo hello < infile >> out2 | <out2 wc -l > out3 > out4 > out5",
		// "echo hello > outfile1 | wc -l > outfile2",
		// "echo 42 | wc -l "
		// "ls | cat",
		// "<< stop cat | grep 42 | wc -l"
		// "echo hello > infile | < infile grep ll"
		// "cat << stop /dev/urandom | head -n 5",
		// "./minishell"
		// "<< stop1 cat "
		// "<< stop1 cat > out1 | echo 42 | <<stop2 cat > out2 | < out2 wc -l",
		// "<< stop1 cat >> outfile",
		// "cat < Makefile"

	};
}

t_token *lexer(char *line, t_minishell *minishell)
{
	t_token *head = apply_lexer(line);

	if (is_unclosed_quotes(&head))
	{
		write(2, "Unclosed quotes\n", 16);
		free_tokens(head);
		minishell->exit_status = 2;
		return (0);
	}
	return head;
}

t_cmd *tokenizer(t_token *head, char **env, t_minishell *minishell)
{
	merge_envs(&head);
	expand_env(&head, env, minishell);
	concatenate_minus(&head);
	concate_quotes(&head);
	merge_redirections_heredoc(&head);
	validate_absolute_path(&head);
	validate_commands(minishell);
	if (!is_quote_error(&head))
	{
		write(2, "syntax error near unexpected token `newline'1\n", 46);
		free_tokens(head);
		minishell->exit_status = 2;
		return (0);
	}
	remove_quotes(&head);
	concate_leftover_strings(&head);
	remove_whitespaces(&head);
	validate_filename(&head);
	if (validate_heredoc(&head, minishell))
		return (0);
	validate_dollarsign(&head);
	validate_commands_two(&head);
	validate_builtins(&head);

	if (head->type == WORD)
	{
		write(2, "syntax error near unexpected token `newline'2\n", 46);
		free_tokens(head);
		minishell->exit_status = 127;
		return (0);
	}
	// print_tokens(head);
	
	t_cmd *cmd_node = split_to_pipes(&head);
	free_tokens(head);
	return cmd_node;
}

// void executor(t_cmd *cmd_node, char **env, t_token *head, t_env **env_list)
int executor(t_minishell *minishell)
{

	t_env **env_list = NULL;
	open_files(&minishell->cmd_node);

	if (is_heredoc(minishell->cmd_node))
	{
		printf("=============sequence===========\n");
		fprintf(stderr, C_BLUE "sequence\n" C_RESET);
		return (sequential_executor(minishell));
	}
	else
	{
		t_pipex pipex = update_pipe_fds(&minishell->cmd_node, minishell->env);
		minishell->pipex = &pipex;
		fprintf(stderr, C_BLUE "parallel\n" C_RESET);
		return (parallel_executor(minishell));
	}
}

void print_env_in_yellow(char **env)
{
	int i = 0;
	fprintf(stderr, C_YELLOW "=================== env ===================\n" C_RESET);
	while (env[i])
	{
		fprintf(stderr, C_YELLOW "%s\n" C_RESET, env[i]);
		i++;
	}
}

#include <signal.h>

void ft_newline(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void is_command_in_every_pipe(t_cmd **cmd_node)
{
	t_cmd *head;
	head = *cmd_node;
	while (head)
	{
		if (head->cmd_full[0] == NULL)
			head->exit_status = 127;
		head = head->next;
	}
}

void	print_env_sorted(char **env, int env_len);

void free_minishell(t_minishell *minishell)
{
	free_tokens(minishell->token);
	free_cmd_nodes(&minishell->cmd_node);
	int i = -1;
	
}

int is_only_spaces(char *line)
{
	int i = 0;
	if (!*line)
		return (1);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n'
			&& line[i] != '\v' && line[i] != '\f' && line[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}

char **ft_dup_env(char **env)
{
	int i = 0;
	char **new_env;

	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}


int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_minishell *minishell;

	minishell = malloc(sizeof(t_minishell));
	minishell->env = ft_dup_env(env);
	minishell->exit_status = 0;
	minishell->token = NULL;
	minishell->cmd_node = NULL;
	minishell->pipex = NULL;
	minishell->oldpwd = NULL;
	signal(SIGINT, ft_newline);
	signal(SIGQUIT, SIG_IGN);
	
	char *lines[] = {
		// "ls | ls -la > outfile | cat -e | wc -l > outfile",
		// "wc -l < infile | grep m < infile",
		// "ls",
		// "wc -l < infile",
		// "ls | cat | grep m | wc -l",
		// "ls - la | wc",
		// "<< stop cat | wc -l" ,
		// "<< stop cat",
		// "       ",
		// "echo hello",
		// "sdfsdf",
		// "echo $?",
		// "echo $USER",
		// "echo $HOME",
		// "echo $TEXT",
		// "$USER",
		// "pwd",
		// "env"
		// "pwd | wc -l",
		// "cd ..", 
		// "cd", 
		// "cd -",
		// "cd src",
		// "cd sskfls",
		// // "pwd",
		// "cd | wc -l | grep 1", 
		// "echo \"hello 42\"",
		// "echo \"hello 42\" | wc -l",
		"env",
		// "env | wc -l",
		// "echo USER | grep USER",
		// "env > out1",
		// " env | grep x | wc -l",
		// check builtins with heredoc,
		"export x=4 a=3", 
		"env"
		// "export"
		};
	
	int i = 0;
	while (i < sizeof(lines) / sizeof(char *))
	{	
		// char *line = readline("minishell$ ");
		// add_history(line);
		char *line = lines[i++];
		// print_env_in_yellow(our_env);
		// fprintf(stderr,"readed line = %s\n", line);
		printf("readed line = {%s}\n", line);

		if (is_only_spaces(line))
		{
			free_minishell(minishell);
			// free(line);
			continue;
		}

		minishell->token = lexer(line, minishell);
		if (!minishell->token)
		{
			fprintf(stderr, C_GREEN "exit_status = %d\n" C_RESET, minishell->exit_status);
			// free(line);
			continue;
		}
		minishell->cmd_node = tokenizer(minishell->token, minishell->env, minishell);
		if (!minishell->cmd_node)
		{
			fprintf(stderr, C_GREEN "exit_status = %d\n" C_RESET, minishell->exit_status);
			// free(line);
			continue;
		}
		// print_tokens(minishell->token);
		
		is_command_in_every_pipe(&minishell->cmd_node);
		first_last_cmd(&(minishell->cmd_node));

		minishell->exit_status = executor(minishell);
		// print_t_cmd(minishell->cmd_node);

		fprintf(stderr, C_GREEN "final_exit_status = %d\n" C_RESET, minishell->exit_status);
		// free(line);
		// printf("pid = %d\n", getpid());

		free_minishell(minishell);
	}
	i = -1;
	if (minishell->env)
	{
		while (minishell->env[++i]) 
			free(minishell->env[i]);
		free(minishell->env);
	}
	free(minishell->oldpwd);
	free(minishell);
	return (0);
}




// int main(int argc, char **argv, char **env)
// {
// 	(void)argc;
// 	(void)argv;
// 	t_minishell *minishell;

// 	minishell = malloc(sizeof(t_minishell));
// 	minishell->env = env;
// 	minishell->exit_status = 0;
// 	minishell->token = NULL;
// 	minishell->cmd_node = NULL;
// 	minishell->pipex = NULL;
// 	signal(SIGINT, ft_newline);
// 	signal(SIGQUIT, SIG_IGN);

// 	while (TRUE)
// 	{	
// 		char *line = readline("minishell$ ");
// 		add_history(line);
		
// 		// print_env_in_yellow(our_env);
// 		// fprintf(stderr,"readed line = %s\n", line);
// 		printf("readed line = {%s}\n", line);
// 		if (!line)
// 		{
// 			// free_minishell(minishell);
// 			free_tokens(minishell->token);
// 			free(minishell);
// 			free(line);
// 			printf("exit\n");
// 			return (0);
// 		}
// 		// if (is_only_spaces(line))
// 		// {
// 		// 	free_minishell(minishell);
// 		// 	free(line);
// 		// 	continue;
// 		// }

// 		minishell->token = lexer(line, minishell);
// 		// if (!minishell->token)
// 		// {
// 		// 	fprintf(stderr, C_GREEN "exit_status = %d\n" C_RESET, minishell->exit_status);
// 		// 	free(line);
// 		// 	continue;
// 		// }
// 		// minishell->cmd_node = tokenizer(minishell->token, minishell->env, minishell);
// 		// if (!minishell->cmd_node)
// 		// {
// 		// 	fprintf(stderr, C_GREEN "exit_status = %d\n" C_RESET, minishell->exit_status);
// 		// 	free(line);
// 		// 	continue;
// 		// }
// 		// is_command_in_every_pipe(&minishell->cmd_node);
// 		// first_last_cmd(&(minishell->cmd_node));


// 		// // print_tokens(minishell->token);
// 		// // print_t_cmd(minishell->cmd_node);


// 		// minishell->exit_status = executor(minishell);

// 		// fprintf(stderr, C_GREEN "final_exit_status = %d\n" C_RESET, minishell->exit_status);
// 		// free(line);
// 		// printf("pid = %d\n", getpid());
// 		// free_tokens(minishell->token);
// 		// free(minishell->token);
// 		// free_minishell(minishell);
// 	}
// 	return (0);
// }

