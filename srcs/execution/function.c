/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubourre <lubourre@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 14:44:53 by lubourre          #+#    #+#             */
/*   Updated: 2021/04/14 16:47:07 by lubourre         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char *str, int option)
{
	if (str)
		write(1, str, ft_strlen(str));
	if (!option)
		write(1, "\n", 1);
}

// a refaire
void	env(char **envp)
{
	register int i;
	
	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

void	ft_exit(void)
{
	write(1, "exit\n", 5);
	exit(0);
}