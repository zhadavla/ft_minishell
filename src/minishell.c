#include <stdio.h>
#include <assert.h>

#include "../includes/minishell.h"

void test_parser_tokeniser()
{
	char *tests[] = {
		"grep $hello file"
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
		printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
		print_tokens(head);
		free_tokens(head);
	}	
}


/**
 * Replace $ENV with value from env
 * if there is no such env variable, replace with empty string
*/
t_token *expand_env(t_token *token, char **env)
{
	int i;
	
	if (token->type != ENV_VARIBLE)
		return token;
	i = 0;
	while (env[++i])
	{

	}

}

int	main(int argc, char **argv, char **env)
{	
	(void)argc;
	(void)argv;
	// for (int i = 0; env[i] != NULL; i++)
	// 	printf("%s\n", env[i]);
		
	test_parser_tokeniser();
	// char *test = "grep   \"fsd hesdagsadgasdgasdllo\" \"world\"";

	// // printf("%s\n", ft_substr(test, 0, 4));

	// t_token *head = apply_lexer(test);
	// print_tokens(head);
	// print_tokens(head);
	return (0);
}