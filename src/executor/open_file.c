/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:47:30 by mnurlybe          #+#    #+#             */
/*   Updated: 2023/09/23 18:40:26 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Opens files for reading, if there's no file, exit with error
 */
static int	open_infile(char **file_names, t_cmd **cmd_node)
{
	int	fd;
	int	i;

	i = 0;
	if (!file_names || !(*cmd_node)->infile_name)
		return (0);
	while (file_names[i])
	{
		fd = open(file_names[i], O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(file_names[i], 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd("No such file or directory\n", 2);
			return (1);
		}
		i++;
	}
	(*cmd_node)->infile_fd = fd;
	return (0);
}

/**
 *  Opens (creating) files in  also adds oppened fd to cmd_node
 */
static int	open_outfile(char **file_names, t_cmd **cmd_node)
{
	int	fd;
	int	i;

	i = 0;
	if (!file_names || !(*cmd_node)->outfile_name)
		return (0);
	while (file_names[i])
	{
		if ((*cmd_node)->is_append)
			fd = open(file_names[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(file_names[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(file_names[i], 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd("No such file or directory\n", 2);
			return (1);
		}
		i++;
	}
	if ((*cmd_node)->outfile_name)
		(*cmd_node)->outfile_fd = fd;
	return (0);
}

/**
 * Opens infile and outfile for each command
 */
int	open_files(t_cmd **cmd_node)
{
	t_cmd	*head;

	head = *cmd_node;
	while (head)
	{
		if (open_infile(head->infile_names, &head))
			return (1);
		if (open_outfile(head->outfile_names, &head))
			return (1);
		head = head->next;
	}
	return (0);
}
