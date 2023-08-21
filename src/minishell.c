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
		// "echo test ", //this one writes command and command ?? to be handled in built in
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
		// "env | sort | grep -v SHLVL | grep -v _=",
		// "export | sort | grep -v SHLVL | grep -v _= | grep -v OLDPWD",
		// "grep -v -l",
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
		// "echo test > ls cat ls",  //MEM LEAK!!!!!
		// "ls > file cat | grep 42",
		// "echo test > ls",
		// "echo test > ls >> ls >> ls echo test >> ls cat ls", //MEM LEAK!!!!!
		"echo test > ls1 >> ls2 >> ls3 echo test >> ls4 cat ls5",
		// "> lol echo test lol; cat lol",
		// ">lol echo > test>lol>test>>lol>test mdr >lol test >test; cat test", //MEM LEAK!!!!!
		// "\'cat\' < \"ls\"",
		// "\'cat\' < \"filename\"",
		// "\'cat\' < filname",
		// "cat << ls > ls", //missing 2 frees validate_heredoc 
		// "cat << ls >> ls",
		"sdfsd < f1 <f2 <f3 > o1 hello >> o2 >>o3 sdfs <f4 >o5 sdfsdf",
		// ">> ls ls -l",
		// "< ls cat",
		// "<inifle1 < infile2 cat",
		// "< infile cat > outfile > fil3",
		// "< infile2 grep \"ls -la hello world\" > outfile2",
		// "ls -l -a > outfile3"
		// "<< stop ls",
		// "<< stop ls -l",
		// "<< stop",
		// "<<",
		// "echo 42 |"
	};
	 for (long unsigned int i = 0; i < sizeof(tests) / sizeof(char *); i++)
	{
		printf("\n\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n");

		printf("%s\n", tests[i]);
		t_token *head = apply_lexer(tests[i]);
		if (is_unclosed_quotes(&head))
		{
			write(2, "Unclosed quotes\n", 16);
			free_tokens(head);
			exit(EXIT_SUCCESS);
		}

		merge_envs(&head);
		expand_env(&head, env);
		concate_quotes(&head);
		merge_redirections_heredoc(&head);
		validate_commands(&head, env);
		concate_leftover_strings(&head);
		remove_whitespaces(&head);
		remove_quotes(&head);
		validate_filename(&head);
		validate_heredoc(&head);
		validate_dollarsign(&head);
		validate_commands_two(&head);


		t_cmd *tmp2 = malloc(sizeof(t_cmd));
		init_cmd_node(&tmp2);
		handle_in_out_files(&head, &tmp2);

		// split to pipes and fill in the information in cmd node for each command
		// t_cmd *tmp = split_to_pipes(&head);
		// print_t_cmd(tmp);
		// free_cmd_nodes(&tmp);
		// free(tmp);

		print_tokens(head);
		
		free_tokens(head);
	}
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	// for (int i = 0; env[i] != NULL; i++)
	// 	printf("%s\n", env[i]);
	// printf("%s\n", get_env_value("$PWD", env));
	test_parser_tokeniser(env);
	// char *test = "grep   \"fsd hesdagsadgasdgasdllo\" \"world\"";

	// // printf("%s\n", ft_substr(test, 0, 4));

	// t_token *head = apply_lexer(test);
	// print_tokens(head);
	// print_tokens(head);
	return (0);
}