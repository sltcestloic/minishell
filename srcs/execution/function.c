/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubourre <lubourre@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 14:44:53 by lubourre          #+#    #+#             */
/*   Updated: 2021/04/15 14:52:38 by lubourre         ###   ########lyon.fr   */
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

void	env(t_envlst *lst)
{
	while (lst->next)
	{
		if (lst->value)
		{
			ft_putstr_fd(lst->name, 1);
			ft_putstr_fd(lst->value, 1);
			write(1, "\n", 1);
		}
		lst = lst->next;
	}
}

void	ft_exit(t_free *to_free)
{
	ft_free(to_free);
	write(1, "exit\n", 5);
	exit(0);
}