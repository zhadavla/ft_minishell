/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:47:30 by mnurlybe          #+#    #+#             */
/*   Updated: 2023/08/25 20:44:59 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Opens files for reading, if there's no file, exit with error
*/
static void	open_infile(char **file_names, t_cmd **cmd_node)
{
	int	fd;
	int	i;

	i = 0;
	if (!file_names || !(*cmd_node)->infile_name)
		return ;
	while (file_names[i])
	{
		fd = open(file_names[i], O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(file_names[i], 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd("No such file or directory\n", 2);
			exit(NO_FILE_EXISTS);
		}
		i++;
	}
	if ((*cmd_node)->infile_name)
		printf("infile name: %s fd: %d\n", (*cmd_node)->infile_name, fd);
	(*cmd_node)->infile_fd = fd;
}

/**
 *  Opens (creating) files in  also adds oppened fd to cmd_node
 */
static void	open_outfile(char **file_names, t_cmd **cmd_node)
{
	int	fd;
	int	i;

	i = 0;
	if (!file_names || !(*cmd_node)->outfile_name)
		return ;
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
			exit(NO_FILE_EXISTS);
		}
		i++;
	}
	if ((*cmd_node)->outfile_name)
		(*cmd_node)->outfile_fd = fd;
}

/**
 * Opens infile and outfile for each command
*/
void	open_files(t_cmd **cmd_node)
{
	t_cmd *head;

	head = *cmd_node;
	while (head)
	{
		open_infile(head->infile_names, &head);
		open_outfile(head->outfile_names, &head);
		head = head->next;
	}
}