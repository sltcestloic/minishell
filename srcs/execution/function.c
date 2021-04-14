/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubourre <lubourre@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 14:44:53 by lubourre          #+#    #+#             */
/*   Updated: 2021/04/14 16:19:34 by lubourre         ###   ########lyon.fr   */
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



void	set_env(char **envp, t_envlst *lst)
{
	register int	i;

	i = 0;
	while (envp[i])
	{
		
		i++;
	}
}

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