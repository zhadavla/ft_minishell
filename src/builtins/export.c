/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 13:54:06 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/20 19:52:51 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*create_env_copy(char **env)
{
	t_env	*head;
	t_env	*tmp;
	int		i;

	head = NULL;
	tmp = NULL;
	i = -1;
	while (env[++i])
	{
		if (!head)
		{
			head = (t_env *)malloc(sizeof(t_env));
			head->next = NULL;
			head->full_env = ft_strdup(env[i]);
			// fprintf(stderr, C_YELLOW "%s\n" C_RESET, head->full_env);
			// fprintf(stderr, "\e[32mkey: %s\e[0m\n", head->key);
			// fprintf(stderr, "\e[31mvalue: %s\e[0m\n", head->value);
			tmp = head;
		}
		else
		{
			tmp->next = (t_env *)malloc(sizeof(t_env));
			tmp = tmp->next;
			tmp->next = NULL;
			tmp->full_env = ft_strdup(env[i]);
			// fprintf(stderr, C_YELLOW "%s\n" C_RESET, tmp->full_env);
			// fprintf(stderr, "\e[32mkey: %s\e[0m\n", tmp->key);
			// fprintf(stderr, "\e[31mvalue: %s\e[0m\n", tmp->value);
		}
	}
	return (head);
}

/**
 * Transform env_list to env_array
 */
char	**t_env_to_array(t_env *env)
{
	char	**env_array;
	t_env	*tmp;
	int		i;

	env_array = NULL;
	tmp = env;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	env_array = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env)
	{
		env_array[i] = ft_strdup(env->full_env);
		i++;
		env = env->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

/**
 * Adds new variable to env_list
 */
void	add_env_variable(t_env **env_list, char *env_text)
{
	t_env	*tmp;

	fprintf(stderr, C_YELLOW "env_text = %s\n" C_RESET, env_text);
	tmp = *env_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = (t_env *)malloc(sizeof(t_env));
	tmp = tmp->next;
	tmp->next = NULL;
	tmp->full_env = ft_strdup(env_text);
}

void	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("declare -x %s\n", env[i]);
		// fprintf(stderr, C_YELLOW "%s\n" C_RESET, env[i]);
		i++;
	}
}

void	ft_swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	clean_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

/**
 * Encloses value in quotation marks
 * split it to key and value
 * and then join them with equal sign
 */
void	quotation_marks_after_equal_sign(char **env, int env_len)
{
	return;
	// int		i;
	// int		j;
	// char	*tmp;
	// char	*key;
	// char	*value;

	// key = NULL, value = NULL, tmp = NULL;
	// i = -1;
	// while (++i < env_len)
	// {
	// 	j = -1;
	// 	while (env[i][++j] != '=')
	// 		;
	// 	fprintf(stderr, C_YELLOW "j = %d\n" C_RESET, j);
	// 	key = ft_substr(env[i], 0, j);
	// 	value = ft_substr(env[i], j + 1, ft_strlen(env[i]) - j);
	// 	tmp = ft_strjoin(key, "=\"");
	// 	key = ft_strjoin(tmp, value);
	// 	free(value);
	// 	tmp = ft_strjoin(key, "\"");
	// 	free(env[i]);
	// 	env[i] = ft_strdup(tmp);
	// 	free(tmp);
	// }
}
/**
 * Sorts env_list alphabetically by key
 * using insert sort
 */
void	print_env_sorted(char **env, int env_len)
{
	char	**sorted_env;
	int		i;
	int		j;
	int		len;

	sorted_env = (char **)malloc(sizeof(char *) * (env_len + 1));
	i = -1;
	while (++i < env_len)
		sorted_env[i] = ft_strdup(env[i]);
	sorted_env[env_len] = NULL;
	i = -1;
	while (++i < env_len)
	{
		j = -1;
		while (++j < i)
		{
			len = ft_strlen(sorted_env[i]) > ft_strlen(sorted_env[j]) ? ft_strlen(sorted_env[i]) : ft_strlen(sorted_env[j]);
			if (ft_strncmp(sorted_env[i], sorted_env[j], len) < 0)
				ft_swap(&sorted_env[i], &sorted_env[j]);
		}
	}
	sorted_env[env_len] = NULL;
	quotation_marks_after_equal_sign(sorted_env, env_len);
	fprintf(stderr, C_YELLOW "i = %d env_len = %d\n" C_RESET, i, env_len);
	print_env(sorted_env);
	clean_env(sorted_env);
}

/**
 * in each command, starging from 1
 * should be only NAME=VALUE
 * name should be only letters, digits and underscores
 * value should be string, enclosed in quotation marks
 */
int	check_validity_one(char *full_assignment)
{
	int	i;

	i = 0;
	// if (full_assignment[i] == '=' || ft_isdigit(full_assignment[i]))
	// 	return (FALSE);
	// while (full_assignment[i] != '=')
	// {
	// 	if (!ft_isalnum(full_assignment[i]) && full_assignment[i] != '_')
	// 		return (FALSE);
	// 	i++;
	// }
	// i++;
	// if (full_assignment[i] != '\"')
	// 	return (FALSE);
	// i++;
	// while (full_assignment[i] != '\"')
	// {
	// 	if (!ft_isprint(full_assignment[i]))
	// 		return (FALSE);
	// 	i++;
	// }
	return (TRUE);
}

/**
 * Checks for validity of each command
 */
int	check_validity(char **commands)
{
	int	i;

	i = 1;
	while (commands[i])
	{
		if (!check_validity_one(commands[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	write_env_to_file(char **env, int fd)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd(env[i], fd);
		ft_putstr_fd("\n", fd);
		i++;
	}
}

/**
 * using read, write, open, close
 */
char	**get_env_from_file(int fd)
{
	char	**env;
	char	*line;
	int		i;

	i = 0;
	while (get_next_line(fd))
	{
		i++;
		free(line);
	}
	env = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	close(fd);
	fd = open(".env", O_RDONLY);
	while (TRUE)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		env[i] = ft_strdup(line);
		free(line);
		i++;
	}
	return (env);
}

/**
 * Creates file if it doesn't exist
 * Returns fd
 */
int	create_file_if_not_exists(void)
{
	int	fd;

	fd = open("./tmp/.env", O_RDONLY);
	if (fd == -1)
	{
		fd = open("./tmp/.env", O_CREAT | O_RDWR, 0777);
		return (fd);
	}
	return (fd);
}

void	add_env_to_file(char **commands, char **env, int fd)
{
	int	i;

	i = 1;
	while (commands[i])
	{
		ft_putstr_fd(commands[i], fd);
		ft_putstr_fd("\n", fd);
		i++;
	}
}

void	ft_export(t_minishell *minishell)
{
	int len = 0;
	char **env = minishell->env;
	char **commands = minishell->cmd_node->cmd_full;

	while (env[len])
	{
		fprintf(stderr, C_BLUE "%s\n" C_RESET, env[len]);
		len++;
	}

	if (!commands[0])
		fprintf(stderr, "export: not enough arguments\n");
	if (!commands[1])
	{
		print_env_sorted(env, len);
		return ;
	}
	if (!check_validity(commands))
	{
		ft_putstr_fd("minishell: export: {", 2);
		ft_putstr_fd(commands[1], 2);
		ft_putstr_fd("}: not a valid identifier\n", 2);
		return ;
	}
	else
	{
		minishell->env_list = create_env_copy(env);
		int i = -1;
		while (commands[++i])
			add_env_variable(&minishell->env_list, commands[i]);
		minishell->env = t_env_to_array(minishell->env_list);
		print_env_in_yellow(minishell->env);
		return;
	}
}