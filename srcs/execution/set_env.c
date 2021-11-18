/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubourre <lubourre@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 17:21:55 by lubourre          #+#    #+#             */
/*   Updated: 2021/11/18 18:33:20 by lubourre         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_equal_concatenate(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+')
		{
			if (str[i + 1] == '=')
			{
				return (2);
			}
			else
				return (-1);
		}
		else if (str[i] == '=')
		{
			return (1);
		}
		else
			i++;
	}
	return (0);
}

void	update_env_value(t_shell *shell, char **arg)
{
	t_envlst	*item;
	t_free		*o;
	int			i;

	i = 1;
	o = shell->to_free;
	while (arg[i])
	{
		item = find_in_list(copy_name(arg[i], shell), shell->env_var);
		if (is_equal_concatenate(arg[i]) == -1)
		{
			ft_putstr_fd("minishell: export: ", 2);
			ft_putstr_fd(arg[i], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			last_exit = 1;
		}
		else if (item && is_equal_concatenate(arg[i]) == 1)
			item->value = copy_value(arg[i], shell);
		else if (item && is_equal_concatenate(arg[i]) == 2)
			item->value = ft_strjoin(item->value, copy_value(arg[i], shell), o);
		else if (!item)
			new_env_elem(arg[i], shell);
		i++;
	}
}

void	new_env_elem(char *str, t_shell *shell)
{
	t_envlst	*ptr;

	if ((str[0] >= '0' && str[0] <= '9') || str[0] == '=' || str[0] == '+')
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		last_exit = 1;
		return ;
	}
	ptr = (t_envlst *)ft_malloc(sizeof(t_envlst), &(shell->to_free));
	if (ptr)
	{
		ptr->name = copy_name(str, shell);
		ptr->value = copy_value(str, shell);
		ptr->next = 0;
	}
	if (!ptr || !ptr->name)
		ft_exit(shell->to_free);
	if (shell->env_var)
		last_lst_elem(shell->env_var)->next = ptr;
	else
		shell->env_var = ptr;
}

void	remove_env_elem(char **arg, t_shell *shell)
{
	t_envlst	*ptr;
	int			i;

	i = 0;
	while (arg[i])
	{
		if ((arg[i][0] >= '0' && arg[i][0] <= '9') || arg[i][0] == '='\
		|| arg[i][0] == '+' || arg[i][0] == '-')
		{
			ft_putstr_fd("minishell: export: ", 2);
			ft_putstr_fd(arg[i], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			last_exit = 1;
		}
		ptr = shell->env_var;
		if (ptr && !ft_strcmp(ptr->name, arg[i]))
			shell->env_var = ptr->next;
		while (ptr && ptr->next)
		{
			if (!ft_strcmp(ptr->next->name, arg[i]))
				ptr->next = ptr->next->next;
			ptr = ptr->next;
		}
		i++;
	}
}

void	set_env(char **envp, t_shell *shell)
{
	register int	i;

	i = 0;
	while (envp[i])
	{
		new_env_elem(envp[i], shell);
		i++;
	}
}
