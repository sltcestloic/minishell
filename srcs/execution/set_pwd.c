/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubourre <lubourre@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:03:06 by lubourre          #+#    #+#             */
/*   Updated: 2021/04/17 13:02:58 by lubourre         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_pwd(t_shell *shell)
{
	t_envlst	*ptr;

	ptr = shell->env_var;
	while(ptr && ft_strcmp(ptr->name, "PWD"))
	{
		ptr = ptr->next;
	}
	if (ptr)
		getcwd(ptr->value, 10000);
	getcwd(shell->pwd, 10000);
}

void	change_pwd(t_shell *shell, char *str)
{
	t_envlst	*ptr;

	chdir(str);
	ptr = shell->env_var;
	while(ptr && ft_strcmp(ptr->name, "PWD"))
	{
		ptr = ptr->next;
	}
	if (ptr)
		getcwd(ptr->value, 10000);
	getcwd(shell->pwd, 10000);
}

void	pwd(t_shell *shell)
{
	ft_putstr_fd(shell->pwd, 1);
}