/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzhadan <vzhadan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:54:08 by vzhadan           #+#    #+#             */
/*   Updated: 2023/09/23 16:14:51 by vzhadan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(char **cmd_full)
{
	int	i;

	i = 1;
	while (cmd_full[i])
	{
		printf("%s", cmd_full[i]);
		if (cmd_full[i + 1])
			printf(" ");
		i++;
	}
	if (i == 1 || ft_strncmp(cmd_full[1], "-n", 2))
		printf("\n");
}
