#include <stdio.h>
#include <assert.h>

#include "../includes/minishell.h"

void test_parser_tokeniser(char **env)
{
	char *tests[] = {
		"grep $PWD file",
		"grep $PW D file",
		"grep $ PWD file",
		"grep $PWDG file",
		"grep $ file",
		// "grep   \"fsd hesdagsadgasdgasdllo\" \"world\"",
		// "cat tests/lorem.txt | grep arcu | cat -e",
		// "ls|ls|ls|ls|ls|ls|ls|ls|",
		// "echo \"$TEST\"",
		// "\"'\"",
		// "export TE+S=T=\"\" ;\' $ENV_SHOW\'",
		// "cho test > ls >> ls >> ls ; echo test >> ls; cat ls", 
		// "<<",
		// "<",
		// "echo testing multi >>; echo \"test 1 ; < | and 2\" ; cat \'tests/lorem.txt\' | grep Lorem"
	};
	for (long unsigned int i = 0; i < sizeof(tests)/ sizeof(char *); i++)
	{
		printf("%s\n", tests[i]);
		t_token *head = apply_lexer(tests[i]);
		merge_envs(&head);
		expand_env(&head, env);
		printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
		print_tokens(head);
		free_tokens(head);
	}	
}


int	main(int argc, char **argv, char **env)
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