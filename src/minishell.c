#include <stdio.h>
#include <assert.h>

#include "../includes/minishell.h"

// void test_num_of_elems_split(void)
// {
// 	// printf("%d\n", get_num_of_elems("Hello, world!"));
	
// 	// assert(get_num_of_elems("Hello, world!") == 2);
// 	// assert(get_num_of_elems("!") == 1);
// 	// assert(get_num_of_elems("grep \'hello") == -1);
// 	// assert(get_num_of_elems("grep \"hello") == -1);
// 	// assert(get_num_of_elems("grep \'hello\'") == 2);
// 	assert(get_num_of_elems("grep \"hello\"") == 2);
// 	// assert(get_num_of_elems("grep \'hello\' \'world\'") == 3);
// 	// assert(get_num_of_elems("grep \"hello\" \"world\"") == 3);	
// }

void test_parser_tokeniser()
{
	char *tests[] = {
		"grep   \"fsd hesdagsadgasdgasdllo\" \"world\"",
		"cat tests/lorem.txt | grep arcu | cat -e",
		"ls|ls|ls|ls|ls|ls|ls|ls|",
		"echo \"$TEST\"",
		"\"'\"",
		"export TE+S=T=\"\" ;\' $ENV_SHOW\'",
		"cho test > ls >> ls >> ls ; echo test >> ls; cat ls", 
		"<<",
		"<",
		"echo testing multi >>; echo \"test 1 ; < | and 2\" ; cat \'tests/lorem.txt\' | grep Lorem"
	};
	for (int i = 0; i < sizeof(tests)/ sizeof(char *); i++)
	{
		t_token *head = apply_lexer(tests[i]);
		printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
		print_tokens(head);
		// free_tokens(head);
	}	
}


int	main(void)
{	
	test_parser_tokeniser();
	// char *test = "grep   \"fsd hesdagsadgasdgasdllo\" \"world\"";

	// // printf("%s\n", ft_substr(test, 0, 4));

	// t_token *head = apply_lexer(test);
	// print_tokens(head);
	// print_tokens(head);
	return (0);
}