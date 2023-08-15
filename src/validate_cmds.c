#include "../includes/minishell.h"

void	free_split(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

char	**get_binaries(char **env)
{
	int	i;

	i = 0;
	while (env[++i])
		if (ft_strnstr(env[i], "PATH=", 5))
			return (ft_split(env[i] + 5, ':'));
	return (NULL);
}

char	*ft_join(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*str;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len1 + len2) + 1);
	if (!s1 || !s2)
		return (NULL);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, len1 + 1);
	ft_strlcat(str, s2, len2 + len1 + 1);
	return (str);
}

int	ft_execute(char *cmd, char **env)
{
	char	**path;
	char	*pathname;
	int		i;

	path = get_binaries(env);
	i = 0;
	while (path[i] != NULL)
	{
		pathname = ft_join(path[i], "/");
		pathname = ft_strjoin(pathname, cmd);
		if (access(pathname, X_OK) == 0)
		{	
			free_split(path);
			free(pathname);
			return (TRUE);
		}
		free(pathname);
		i++;
	}
	free_split(path);
	return (FALSE);
}


void validate_commands(t_token **token, char **g_env)
{
	t_token *head;

	head = *token;

	while (head)
	{
		if (head->type == WORD && head->quote == QUOTE0
			&& ft_execute(head->text, g_env) == TRUE)
			{
				head->type = COMMAND;
				printf("hello we're here\n");
			}
		head = head->next;
	}
}