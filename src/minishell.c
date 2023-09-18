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

t_token *lexer(char *line)
{
	t_token *head = apply_lexer(line);

	if (is_unclosed_quotes(&head))
	{
		write(2, "Unclosed quotes\n", 16);
		free_tokens(head);
		return (0);
	}
	return head;
}

t_cmd *tokenizer(t_token *head, char **env)
{
	merge_envs(&head);
	expand_env(&head, env);
	concatenate_minus(&head);
	concate_quotes(&head);
	merge_redirections_heredoc(&head);
	// it was here: concate_leftover_strings(&head);
	validate_absolute_path(&head);
	validate_commands(&head, env);
	if (!check_quote_error(&head))
	{
		write(2, "syntax error near unexpected token `newline'\n", 46);
		free_tokens(head);
		return (0);
	}
	remove_quotes(&head);
	concate_leftover_strings(&head);
	remove_whitespaces(&head);
	validate_filename(&head);
	validate_heredoc(&head);
	validate_dollarsign(&head);
	validate_commands_two(&head);
	validate_builtins(&head);

	if (head->type == WORD)
	{
		write(2, "syntax error near unexpected token `newline'\n", 46);
		free_tokens(head);
		return (0);
	}
	t_cmd *cmd_node = split_to_pipes(&head);
	// print_t_cmd(cmd_node);
	return cmd_node;
}

void executor(t_cmd *cmd_node, char **env, t_token *head, t_env **env_list)
{

	open_files(&cmd_node);
	first_last_cmd(&cmd_node);

	if (is_heredoc(cmd_node))
	{
		// printf("=============sequence===========\n");
		fprintf(stderr, C_BLUE "sequence\n" C_RESET);
		sequential_executor(cmd_node, env, env_list);
	}
	else{
		t_pipex pipex = update_pipe_fds(&cmd_node, env);
		fprintf(stderr, C_BLUE "parallel\n" C_RESET);
		parallel_executor(pipex, &cmd_node, env, env_list);
	} 
	

	free_cmd_nodes(&cmd_node);
	free(cmd_node);
	free_tokens(head);
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
void	print_env_sorted(char **env, int env_len);
int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	
	t_env *env_copy = create_env_copy(env);
	char **our_env = t_env_to_array(env_copy);
	while (TRUE)
	{	
		char *line = readline("minishell$ ");
		// print_env_in_yellow(our_env);
		// fprintf(stderr,"readed line = %s\n", line);
		printf("readed line = %s\n", line);
		if (!line)
		{
			free(line);
			printf("exit\n");
			return (0);
		}

		t_token *head = lexer(line);
		if (!head)
		{
			free(line);
			continue;
		}
		t_cmd *cmd = tokenizer(head, env);
		if (!cmd)
		{
			free(line);
			continue;
		}

		print_tokens(head);
		print_t_cmd(cmd);

		executor(cmd, our_env, head, &env_copy);
		
		free(line);
		// print_env_in_yellow(t_env_to_array(env_copy));
		printf("pid = %d\n", getpid());
	}
	// test_parser_tokeniser(env);

	return (0);
}
