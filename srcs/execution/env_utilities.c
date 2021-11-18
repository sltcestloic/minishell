/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubourre <lubourre@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 18:33:27 by lubourre          #+#    #+#             */
/*   Updated: 2021/11/18 18:33:48 by lubourre         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_name(char *str, t_shell *shell)
{
	register int	i;
	char			*ptr;

	i = 0;
	while ((str[i] != '+' || str[i] != '=') && str[i])
		i++;
	ptr = ft_malloc(i + 1, &shell->to_free);
	if (!ptr)
		return (ptr);
	i = -1;
	while (str[++i] != '=' && str[i] != '+' && str[i])
		ptr[i] = str[i];
	ptr[i] = 0;
	return (ptr);
}

char	*copy_value(char *str, t_shell *shell)
{
	register int	i;
	register int	j;
	char			*ptr;

	i = 0;
	j = 0;
	while (str[i] != '=' && str[i])
		i++;
	while (str[i + j])
		j++;
	if (j == 0)
		return (NULL);
	i++;
	ptr = ft_malloc(j + 1, &shell->to_free);
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
