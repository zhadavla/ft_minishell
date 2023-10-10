/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julienmoigno <julienmoigno@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:54:08 by vzhadan           #+#    #+#             */
/*   Updated: 2023/10/10 08:48:29 by julienmoign      ###   ########.fr       */
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
