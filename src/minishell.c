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
		"grep $ file"
	};
	char * tests[] = {
		"grep \"hello       $HOME              world\" file",
		"grep \" \""
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