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

		// "echo \"test",
		// "echo $TEST",
		// "echo \"df s\"",
		// "echo \"$TEST\"",
		// "echo '$TEST'",
		// "echo \"$TEST$TEST$TEST\"",
		// "echo \"$TEST$TEST=lol$TEST\"",
		// "echo \"   $TEST lol $TEST\"",
		// "echo $TEST$TEST$TEST",
		// "echo $TEST$TEST=lol$TEST",
		// "lol",
		// "echo    $TEST lol $TEST",
		// "echo test ",
		// " test ",
		// " test",
		// "echo \"\\$TEST\"",
		// "echo \"$=TEST\"",
		// "echo \"$\"",
		// "echo \"$?TEST\"",
		// "echo \\$TEST\\ $TEST",
		// "echo \"$1TEST\"",
		// "echo \"$T1TEST\"",
		// "env | sort | grep -v SHLVL | grep -v _=",
		// "export | sort | grep -v SHLVL | grep -v _= | grep -v OLDPWD",
		// "export =",
		// "export 1TEST= ;' $ENV_SHO",
		// "export TEST ;' $EXPORT_SHO",
		// "export ",
		// "=",
		// " ; ' $ENV_SHO",
		// "export TES=T=",
		// " ;' $ENV_SHO",
		// "export TE+S=T=",
		// " ;' $ENV_SHO",
		// "export TEST=LOL ; echo $TEST ;\' $ENV_SHO\'",
		// "export TEST=LlOL ; echo $TEST$TEST$TEST=lol$TEST",
		// "export TEST=LOL; export TEST+=LOL ; echo $TEST ;' $ENV_SHO",
		// "ENV_SHO",
		// "EXPORT_SHO",
		// "export TEST=\"ls       -l     - a\" ; echo $TEST ; $LS ; \' $ENV_SHO"
		// "echo test > ls ; cat ls",
		// "echo test > ls >> ls >> ls ; echo test >> ls; cat ls",
		// "> lol echo test lol; cat lol",
		// ">lol echo > test>lol>test>>lol>test mdr >lol test >test; cat test",
		// "\'cat\' < \"ls\"",
		// "cat << ls > ls",
		// // "cat \"<< ls\" \'>> ls",
		// ">> ls ls -l",
		// "< ls cat"
		"< infile cat > outfile",
		"< infile2 grep \"ls -la hello world\" > outfile2"
	};
	 for (long unsigned int i = 0; i < sizeof(tests) / sizeof(char *); i++)
	{
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
		remove_whitespaces(&head);
		concate_redirections_heredoc(&head);
		validate_commands(&head, env);
		validate_filename(&head);
		// char **test = create_full_command(head);
		// while (*test)
		// {
		// 	printf("command %s\n", *test);
		// 	test++;
		// }
		// printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
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