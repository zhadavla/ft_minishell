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



int	main(void)
{	
	char *test = "grep   \"fsd hesdagsadgasdgasdllo\" \"world\"";

	// printf("%s\n", ft_substr(test, 0, 4));

	t_token *head = apply_lexer(test);
	print_tokens(head);
	// print_tokens(head);
	return (0);
}