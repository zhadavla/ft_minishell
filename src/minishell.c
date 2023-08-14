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
		"echo \"df s\"",
		"echo \"$TEST\"",
		"echo '$TEST'",
		"echo \"$TEST$TEST$TEST\"",
		"echo \"$TEST$TEST=lol$TEST\"",
		"echo \"   $TEST lol $TEST\"",
		"echo $TEST$TEST$TEST",
		"echo $TEST$TEST=lol$TEST",
		"lol",
		"echo    $TEST lol $TEST",
		"echo test ",
		" test ",
		" test",
		"echo \"\\$TEST\"",
		"echo \"$=TEST\"",
		"echo \"$\"",
		"echo \"$?TEST\"",
		"echo \\$TEST\\ $TEST",
		"echo \"$1TEST\"",
		"echo \"$T1TEST\"",
		"env | sort | grep -v SHLVL | grep -v _=",
		"export | sort | grep -v SHLVL | grep -v _= | grep -v OLDPWD",
		"export =",
		"export 1TEST= ;' $ENV_SHO",
		"export TEST ;' $EXPORT_SHO",
		"export ",
		"=",
		" ; ' $ENV_SHO",
		"export TES=T=",
		" ;' $ENV_SHO",
		"export TE+S=T=",
		" ;' $ENV_SHO",
		"export TEST=LOL ; echo $TEST ;' $ENV_SHO",
		"export TEST=LOL ; echo $TEST$TEST$TEST=lol$TEST",
		"export TEST=LOL; export TEST+=LOL ; echo $TEST ;' $ENV_SHO",
		"ENV_SHO",
		"EXPORT_SHO",
		"export TEST=\"ls       -l     - a\" ; echo $TEST ; $LS ; \' $ENV_SHO"
	};
	 for (long unsigned int i = 0; i < sizeof(tests) / sizeof(char *); i++)
	{
		printf("%s\n", tests[i]);
		t_token *head = apply_lexer(tests[i]);
		merge_envs(&head);
		expand_env(&head, env);
		concate_quotes(&head);
		printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
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