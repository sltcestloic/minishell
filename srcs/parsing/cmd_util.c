/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 08:46:41 by lbertran          #+#    #+#             */
/*   Updated: 2021/11/17 08:46:48 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_bzero(t_cmd *cmd, int args)
{
	int	i;

	i = 0;
	cmd->value = (char **)ft_malloc(
			sizeof(char *) * args, &cmd->shell->to_free);
	if (!cmd->value)
		ft_malloc_error(cmd->shell->to_free);
	while (i < args)
		cmd->value[i++] = 0;
}

void	quote_cmd(t_parser *parser, char c)
{
	if (c == '"' && !parser->s_quote)
		parser->d_quote = !parser->d_quote;
	else if (c == '\'' && !parser->d_quote)
		parser->s_quote = !parser->s_quote;
}

void	cmd_addback(t_cmd *cmd, t_cmd *add)
{
	t_cmd	*current;

	current = cmd;
	while (1)
	{
		if (!current->next)
			break ;
		current = current->next;
	}
	add->next = NULL;
	current->next = add;
}

t_cmd	*cmd_last(t_cmd *cmd)
{
	t_cmd	*current;

	current = cmd;
	while (1)
	{
		if (!current->next)
			break ;
		current = current->next;
	}
	return (current);
}

void	redo_value(t_cmd *cmd)
{
	char	**new_value;
	int		i;
	int		j;

	if (!cmd->value)
		return ;
	new_value = (char **)ft_malloc(sizeof(char *)
			* (ft_splitlen(cmd->value) + 1), &cmd->shell->to_free);
	i = 0;
	j = 0;
	while (cmd->value[i])
	{
		if (cmd->value[i] != (char *)1)
			new_value[j++] = ft_strdup(cmd->value[i], cmd->shell->to_free);
		i++;
	}
	new_value[j] = 0;
	if (new_value[0])
		cmd->value = new_value;
	else
		cmd->value = NULL;
}
