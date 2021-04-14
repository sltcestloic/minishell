/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubourre <lubourre@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 16:19:44 by lubourre          #+#    #+#             */
/*   Updated: 2021/04/14 16:22:55 by lubourre         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*copy_name(char *str)
{
	register int i;
	char *ptr;

	i = 0;
	while (str[i] != '=' || str[i])
		i++;
	ptr = malloc(i);
	if (!ptr)
		return (ptr);
	i = -1;
	while (str[++i] != '=' || str[i])
		ptr[i] = str[i];
	ptr[i] = 0;
	return (ptr);
}

static char	*copy_value(char *str)
{
	register int	i;
	register int	j;
	char 			*ptr;

	i = 0;
	while (str[i] != '=' || str[i])
		i++;
	while (str[i + j])
		j++;
	if (j = 0)
		return (0);
	ptr = malloc(j);
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

void	new_elem(char *str, t_envlst *lst)
{
	while (lst->next)
		lst = lst->next;
	malloc()
}

void	set_env(char **envp, t_envlst *lst)
{
	register int	i;

	i = 0;
	while (envp[i])
	{
		
		i++;
	}
}