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

int main(void)
{
	int pipefd[2];
	pipe(pipefd);
	char *tmp = (char *)malloc(8 * sizeof(char));
	strcpy(tmp, "42");
	

	for (int i = 0; i < 5; i++){
		int pid1 = fork();

		if (pid1 == 0)
		{
			if (i == 0 || i == 3)
			{
				
			heredoc()
			}
			printf("excve\n");
			exit(0);
		}
		else 
			wait(NULL);
	}
	
	return 0;
}