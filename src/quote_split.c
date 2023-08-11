#include "libft.h"

#define QUOTE1 '\''
#define QUOTE2 '\"'

int is_quote(char c)
{
	
	return (c == '\'' || c == '\"');
}

int is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f');
}

/**
 * Returns num_of_elems of array of strings splitted by spaces.
 * Doesn't metter how many spaces are in {str}.
 * If there is unclosed quote, returns -1.
 */
int get_num_of_elems(char *str)
{
	int num_of_elems;
	int i;
	char quote;
	bool is_quote_open;

	num_of_elems = 0;
	i = 0;
	while (str[i])
	{
		
		if (is_quote(str[i]))
		{
			quote = str[i];
			if (!ft_strchr(str, str[i]))
				return (-1);
			i++;
			while (str[i] != quote)
				i++;
		}
		while (is_whitespace(str[i]))
		{
			// printf("str[%d] = %c\n", i, str[i]);
			if (is_quote(str[i + 1]))
			{	

				printf("str[%d] = %c\n", i + 1, str[i + 1]);	
				printf("str + i + 2 = %s\n", str + i + 2);
				printf("strchr {%s}\n", ft_strchr(str + i + 2, str[i + 1]));
				if (!ft_strchr(str + i + 2, str[i + 1]))
					return (-1);
			}
				
			if (!is_whitespace(str[i + 1]) && str[i + 1] != '\0')
				num_of_elems++;
			i++;
		}
		i++;
	}
	return (num_of_elems + 1);
}

/**
 * Splits the string {s} using the space ' ' as a delimiter.
 * Doesn't metter how many spaces are in {s}.
 * If there is unclosed quote, returns NULL.
 */

// 	char **split(const char *str)
// {
// 	char **res;

// 	res = (char **)malloc(num_of_elemsof(char *) * (get_num_of_elems(str) + 1));
// }
