/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 08:46:58 by lbertran          #+#    #+#             */
/*   Updated: 2021/11/17 09:05:03 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_space(char *str)
{
	int			i;
	int			count;
	t_parser	parser;

	i = 0;
	count = 0;
	parser = init_parser_nml();
	while (str[i])
	{
		quote_cmd(&parser, str[i]);
		if (str[i] == ' ' && !parser.s_quote && !parser.d_quote)
			count++;
		i++;
	}
	return (count);
}

void	copy_content(char **src, char **dest, t_free *to_free)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = ft_strdup(src[i], to_free);
		i++;
	}
	dest[i] = 0;
}

static void	copy_first_values(t_index *idx, int index,
			char **new_value, t_cmd *cmd)
{
	while (idx->j < index)
	{
		new_value[idx->j] = ft_strdup(cmd->value[idx->j],
				cmd->shell->to_free);
		idx->j++;
	}
}

void	split_cmd(t_cmd *cmd, int i, int spaces, t_free *fr)
{
	char	**new_value;
	char	**end_value;
	t_index	idx;
	int		last;

	idx = init_index();
	last = 0;
	new_value = (char **)ft_malloc(sizeof(char *)
			* (ft_splitlen(cmd->value) + spaces + 1), &fr);
	end_value = (char **)ft_malloc(sizeof(char *)
			* (ft_splitlen(&cmd->value[i]) + 1), &fr);
	copy_content(&cmd->value[i + 1], end_value, fr);
	copy_first_values(&idx, i, new_value, cmd);
	while (cmd->value[i][idx.i])
	{
		if (cmd->value[i][idx.i] == ' ')
		{
			new_value[idx.j++] = ft_strrdup(cmd->value[i], last, idx.i - 1, fr);
			last = idx.i + 1;
		}
		idx.i++;
	}
	new_value[idx.j++] = ft_strrdup(cmd->value[i], last, idx.i - 1, fr);
	copy_content(end_value, &new_value[idx.j], fr);
	cmd->value = new_value;
}

void	split_tokens(t_cmd *cmd)
{
	int	i;
	int	spaces;

	i = 0;
	while (cmd->value[i])
	{
		if (cmd->value[i] == (char *)1)
		{
			i++;
			continue ;
		}
		spaces = has_space(cmd->value[i]);
		if (spaces > 0)
			split_cmd(cmd, i, spaces, cmd->shell->to_free);
		i++;
	}
}
