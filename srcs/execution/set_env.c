/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubourre <lubourre@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 16:19:44 by lubourre          #+#    #+#             */
/*   Updated: 2021/04/16 15:52:29 by lubourre         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

inline static char	*copy_name(char *str)
{
	register int i;
	char *ptr;

	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	ptr = malloc(i + 1);
	if (!ptr)
		return (ptr);
	i = -1;
	while (str[++i] != '=' && str[i])
		ptr[i] = str[i];
	ptr[i] = 0;
	return (ptr);
}

inline static char	*copy_value(char *str)
{
	register int	i;
	register int	j;
	char 			*ptr;

	i = 0;
	j = 0;
	while (str[i] != '=' && str[i])
		i++;
	while (str[i + j])
		j++;
	if (j == 0)
		return (0);
	ptr = malloc(j + 1);
	if (ptr)
	{
		j = 0;
		while (str[i + j])
		{
			ptr[j] = str[i + j];
			j++;
		}
		ptr[j] = 0;
	}
	return (ptr);
}

void	new_env_elem(char *str, t_shell *shell)
{
	t_envlst	*ptr;
	t_envlst	*save;

	save = shell->env_var;
	if (save)
	{
		while (save->next)
			save = save->next;
	ptr = (t_envlst*)ft_malloc(sizeof(t_envlst), &(shell->to_free));
	save->next = ptr;
	}
	else
	{
		ptr = (t_envlst*)ft_malloc(sizeof(t_envlst), &(shell->to_free));
		shell->env_var = ptr;
	}
	if (ptr)
	{
		ptr->name = copy_name(str);
		ptr->value = copy_value(str);
		ptr->next = 0;
	}
	if (!ptr || !ptr->name)
		ft_exit(shell->to_free);
}

void	remove_env_elem(char *name, t_shell *shell)
{
	t_envlst	*ptr;

	ptr = shell->env_var;
	while (ptr->next && ft_strcmp(ptr->next->name, name))
	{
		ptr = ptr->next;
	}
	if (ptr->next)
		ptr->next = ptr->next->next;
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