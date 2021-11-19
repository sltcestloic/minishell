/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubourre <lubourre@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 18:26:19 by lubourre          #+#    #+#             */
/*   Updated: 2021/11/19 11:55:21 by lubourre         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_list(t_envlst *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_envlst	*find_in_list(char *str, t_envlst *ptr)
{
	while (ptr && ft_strcmp(ptr->name, str))
		ptr = ptr->next;
	return (ptr);
}

t_envlst	*last_lst_elem(t_envlst *lst)
{
	t_envlst	*save;

	save = lst;
	while (save->next)
		save = save->next;
	return (save);
}

char	**find_path(t_shell *shell)
{
	t_envlst	*ptr;
	char		**path;

	ptr = find_in_list("PATH", shell->env_var);
	path = NULL;
	if (ptr && ptr->value && ptr->value[0])
	{
		path = ft_split(ptr->value, ':', shell->to_free);
		if (!path)
			ft_malloc_error(shell->to_free);
	}
	return (path);
}

void	ft_exit(t_free *to_free)
{
	ft_free(to_free);
	exit(0);
}
