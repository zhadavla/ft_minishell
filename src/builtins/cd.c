/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 19:14:56 by vzhadan           #+#    #+#             */
/*   Updated: 2023/10/10 17:30:48 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// cd - no directory specified: go to home directory
// cd - directory specified: go to that directory
// cd .. - go to parent directory one step back
// cd . - go to current directory
// cd ../path/to/dir

int	is_str_in_strs(char **strs, char *str)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		if (ft_strncmp(strs[i], str, ft_strlen(str)) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	ft_old_pwd(t_minishell *minishell)
{
	char	*tmp;

	tmp = NULL;
	tmp = getcwd(NULL, 0);
	if (is_str_in_strs(minishell->env, "OLDPWD") == 0)
	{
		ft_putstr_fd(C_RED "cd: OLDPWD not set\n" C_RESET, 2);
		return (4);
	}
	if (chdir(minishell->oldpwd) == -1)
		return (4);
	free(minishell->oldpwd);
	minishell->oldpwd = tmp;
	return (0);
}

int	ft_cd_two(t_minishell *minishell)
{
	free(minishell->oldpwd);
	minishell->oldpwd = getcwd(NULL, 0);
	if (chdir(minishell->cmd_node->cmd_full[1]) == -1)
	{
		ft_putstr_fd(C_RED "cd: No such file or directory\n" C_RESET, 2);
		return (4);
	}
	return (0);
}

void add_oldpwd_pwd_to_env(t_minishell *minishell)
{
	char	*tmp;
	char	*tmp2;

	char *old_pwd = ft_strdup("OLDPWD=");
	char *pwd = ft_strdup("PWD=");
	tmp = ft_strjoin(old_pwd, minishell->oldpwd);
	char *current_wd = getcwd(NULL, 0);
	tmp2 = ft_strjoin(pwd, current_wd);
	free(current_wd);
	int i = -1;
	char **env = minishell->env;
	
	while (env[++i]){
		if (!ft_strncmp(env[i], "OLDPWD=", 7))
		{
			free(env[i]);
			env[i] = tmp;
		}
		if (!ft_strncmp(env[i], "PWD=", 4))
		{
			free(env[i]);		
			env[i] = tmp2;
		}
	}
	
}

int	ft_cd(t_minishell *minishell)
{
	if (minishell->oldpwd == NULL)
		minishell->oldpwd = getcwd(NULL, 0);
	if (minishell->cmd_node->cmd_full[1] == NULL)
	{
		free(minishell->oldpwd);
		minishell->oldpwd = getcwd(NULL, 0);
		if (chdir(getenv("HOME")) == -1){
	
			add_oldpwd_pwd_to_env(minishell);
			return (4);
		}
	}
	else
	{
		if (!ft_strncmp(minishell->cmd_node->cmd_full[1], "-", 1))
		{
			if (ft_old_pwd(minishell) == 4){
				add_oldpwd_pwd_to_env(minishell);
				return (4);
			}
			
		}
		else
		{
			if (ft_cd_two(minishell) == 4){
				add_oldpwd_pwd_to_env(minishell);	
				return (4);
			}
		}
	}
	add_oldpwd_pwd_to_env(minishell);	
	return (0);
}
