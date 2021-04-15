/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 14:56:53 by lbertran          #+#    #+#             */
/*   Updated: 2021/04/15 14:54:17 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*compute_args(t_command *cmd, int has_n)
{
	char	*ret;
	char	*swap;
	int		i;

	i = 0;
	if (ft_splitlen(cmd->args) == 0)
		return (NULL);
	if (!has_n)
		ret = ft_strdup(cmd->args[0]);
	else if (ft_splitlen(cmd->args) > 1)
		ret = ft_strdup(cmd->args[++i]);
	while (cmd->args[++i])
	{
		swap = ft_strjoin(ret, " ");
		free(ret);
		ret = swap;
		swap = ft_strjoin(ret, cmd->args[i]);
		free(ret);
		ret = swap;
	}
	return (ret);
}

void	parse_echo(t_command *cmd)
{
	char	*args;
	int		has_n;

	if (ft_splitlen(cmd->args))
		has_n = ft_strcmp(cmd->args[0], "-n") == 0;
	else
		has_n = FALSE;
	args = compute_args(cmd, has_n);
	echo(args, has_n);
}
