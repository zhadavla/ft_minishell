/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 20:01:54 by vzhadan           #+#    #+#             */
/*   Updated: 2023/08/21 20:11:04 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_token	*create_list_of_files(t_token **till_pipe);
static void		get_infile_names(t_token *token, t_cmd **cmd_node);
static void		get_outfile_names(t_token *token, t_cmd **cmd_node);
static int		count_files(t_token *token, int is_infile_flag);

/**
 * Creates a list of tokens before the pipe
 * and removes the nodes with redirections from the till_pipe list
 */
static t_token	*create_list_of_files(t_token **till_pipe)
{
	t_token	*head;
	t_token	*prev;
	t_token	*list_of_files;

	head = *till_pipe;
	prev = NULL;
	list_of_files = NULL;
	while (head)
	{
		if (is_file(head))
		{
			t_add(&list_of_files, new_token(ft_strdup(head->text), head->len,
					head->type, head->quote));
			prev = head;
			head = head->next;
			remove_node(till_pipe, prev);
		}
		else
			head = head->next;
	}
	return (list_of_files);
}

/**
 * Counts the number of files in the list of tokens
 * is_infile_flag is TRUE if we count infiles
 * is_infile_flag is FALSE if we count outfiles
 */
static int	count_files(t_token *token, int is_infile_flag)
{
	int	count;

	count = 0;
	while (token)
	{
		if (is_infile_flag && is_infile(token))
			count++;
		else if (!is_infile_flag && is_outfile(token))
			count++;
		token = token->next;
	}
	return (count);
}

/**
 * Writes to the cmd_node->infile_names all the infile names
 */
static void	get_infile_names(t_token *token, t_cmd **cmd_node)
{
	t_token	*tmp;
	t_token	*prev;
	int		i;

	prev = NULL;
	i = count_files(token, TRUE);
	(*cmd_node)->infile_names = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	tmp = token;
	while (tmp)
	{
		if (is_infile(tmp))
		{
			prev = tmp;
			(*cmd_node)->infile_names[i] = ft_strdup(tmp->text);
			i++;
		}
		tmp = tmp->next;
	}
	(*cmd_node)->infile_names[i] = NULL;
	if (prev)
		(*cmd_node)->infile_name = ft_strdup(prev->text);
}

/**
 * Writes to the cmd_node the information about outfiles
 * also handles is_append flag by checking the last outfile node
 */
static void	get_outfile_names(t_token *token, t_cmd **cmd_node)
{
	t_token	*tmp;
	t_token	*prev;
	int		i;

	prev = NULL;
	i = count_files(token, FALSE);
	(*cmd_node)->outfile_names = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	tmp = token;
	while (tmp)
	{
		if (is_outfile(tmp))
		{
			prev = tmp;
			(*cmd_node)->outfile_names[i] = ft_strdup(tmp->text);
			i++;
		}
		tmp = tmp->next;
	}
	(*cmd_node)->outfile_names[i] = NULL;
	if (prev && prev->type == REDIR_APPEND)
		(*cmd_node)->is_append = TRUE;
	if (prev)
		(*cmd_node)->outfile_name = ft_strdup(prev->text);
}

void	handle_in_out_files(t_token **token, t_cmd **cmd_node)
{
	t_token *tmp;

	remove_redirections(token);
	tmp = create_list_of_files(token);
	get_infile_names(tmp, cmd_node);
	get_outfile_names(tmp, cmd_node);
	free_tokens(tmp);

	/////////////////////////////////////////////////////////////
	printf("---------------------------------infile names:\n");
	print_array_of_chars((*cmd_node)->infile_names);
	printf("FINAL INFILE NAME: %s\n", (*cmd_node)->infile_name);
	printf("---------------------------------outfile names:\n");
	printf("FINAL OUTFILE NAME: %s\n", (*cmd_node)->outfile_name);
	print_array_of_chars((*cmd_node)->outfile_names);
}