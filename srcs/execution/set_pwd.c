/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubourre <lubourre@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 17:56:28 by lubourre          #+#    #+#             */
/*   Updated: 2021/11/18 17:59:44 by lubourre         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	go_home(t_shell *shell)
{
	t_envlst	*ptr;

	ptr = find_in_list("HOME", shell->env_var);
	if (ptr && ptr->value)
	{
		if (chdir(ptr->value) == -1)
		{
			write(2, "minishell: cd: incorrect HOME path\n", 28);
			last_exit = 1;
		}
	}
	else
	{
		write(2, "minishell: cd: HOME not set\n", 28);
		last_exit = 1;
	}
}

void	set_pwd(t_shell *shell)
{
	t_envlst	*ptr;
	t_envlst	*oldptr;

	ptr = shell->env_var;
	oldptr = shell->env_var;
	while (oldptr && ft_strcmp(oldptr->name, "OLDPWD"))
		oldptr = oldptr->next;
	if (oldptr)
		oldptr->value = NULL;
	while (ptr && ft_strcmp(ptr->name, "PWD"))
		ptr = ptr->next;
	if (ptr)
		getcwd(ptr->value, 10000);
	getcwd(shell->pwd, 10000);
}

void	change_pwd(t_shell *shell, char *str)
{
	t_envlst	*ptr;
	t_envlst	*oldptr;

	last_exit = 0;
	if (str)
	{
		if (chdir(str) == -1 && write(2, "minishell: cd: ", 15))
			perror(str);
		last_exit = 1;
	}
	else
		go_home(shell);
	ptr = find_in_list("PWD", shell->env_var);
	oldptr = find_in_list("OLDPWD", shell->env_var);
	if (oldptr)
		oldptr->value = ptr->value;
	if (ptr)
	{
		ptr->value = ft_malloc(MAXPATHLEN, &shell->to_free);
		getcwd(ptr->value, MAXPATHLEN);
	}
	getcwd(shell->pwd, MAXPATHLEN);
}

void	pwd(t_shell *shell)
{
	last_exit = 0;
	printf("%s\n", shell->pwd);
}
