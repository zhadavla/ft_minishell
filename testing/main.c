#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// void foo()
// {
// 	int pid = fork();
// 	printf("hello\n");
// }

// int main(void)
// {
// 	// int pid1 = fork();
// 	// int pid2 = fork();
// 	// int pid3 = fork();

// 	for (int i = 0; i < 3; i++)
// 	{
// 		int pid = fork();
// 		// printf("hello\n");
// 	}
// 	printf("hello\n");
// 	return 0;
// }
// int SIZE = 2;

// void print_pids(int **pids){

#include <readline/readline.h>

// }
#include <string.h>
char *int_to_str(int num)
{
	char *str = (char *)malloc(10 * sizeof(char));
	int i = 0;
	while (num > 0)
	{
		str[i] = num % 10 + '0';
		num /= 10;
		i++;
	}
	// reverse it
	for (int j = 0; j < i / 2; j++)
	{
		char tmp = str[j];
		str[j] = str[i - j - 1];
		str[i - j - 1] = tmp;
	}
	str[i] = '\0';
	return str;
}

void foo(char *str)
{
	*str = 'a';

}

#include <unistd.h>
int main(int argc, char **argv, char **envp)
{	
	int ac_b = access("/bin/ls", X_OK);
	printf("ac_b = %d\n", ac_b);
	// char *strs[2] = {"./minishell", NULL};
	// printf("hello\n");
	// if (execve("./minishell", strs, envp) == -1)
	// 	fprintf(stderr, " not hello\n");
	return 0;
}
