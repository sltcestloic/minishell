/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 08:46:48 by lbertran          #+#    #+#             */
/*   Updated: 2021/11/20 16:19:23 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_new_cmd(t_cmd *cmd, t_shell *shell)
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)ft_malloc(sizeof(t_cmd), &shell->to_free);
	new_cmd->next = NULL;
	new_cmd->redirect = NULL;
	new_cmd->value = NULL;
	new_cmd->shell = shell;
	if (!new_cmd)
		ft_malloc_error(shell->to_free);
	cmd_last(cmd)->next = new_cmd;
}

static char	*next_word(char *input, t_shell *shell)
{
	t_parser	parser;
	char		*ret;
	int			i;

	i = 0;
	parser.d_quote = 0;
	parser.s_quote = 0;
	while (input[i])
	{
		if (input[i] == '"' && !parser.s_quote)
			parser.d_quote = !parser.d_quote;
		else if (input[i] == '\'' && !parser.d_quote)
			parser.s_quote = !parser.s_quote;
		else if (ft_iswhitespace(input[i])
			&& !parser.s_quote && !parser.d_quote)
			break ;
		i++;
	}
	ret = ft_strrdup(input, 0, i - 1, shell->to_free);
	return (ret);
}

/*
** return la taille du mot ajouté au parser pour qu'il passe a la suite
*/
int	add_arg(t_cmd *cmd, char *input, t_shell *shell)
{
	char	**new_value;
	int		i;

	new_value = malloc(sizeof(char *) * (ft_splitlen(cmd->value) + 2));
	i = 0;
	if (!new_value)
		return (-1);
	while (cmd->value[i])
	{
		new_value[i] = ft_strdup(cmd->value[i], shell->to_free);
		i++;
	}
	new_value[i] = next_word(input, shell);
	new_value[i + 1] = 0;
	cmd->value = new_value;
	return (ft_strlen(cmd->value[i]) - 1);
}

void	cmd_content_loop(t_cmd *cmd, char *input, int *i, t_index *idx)
{
	t_parser	parser;

	parser = init_parser_nml();
	while (input[*i])
	{
		quote_cmd(&parser, input[*i]);
		if (!parser.s_quote && !parser.d_quote)
		{
			if (is_sep(input[*i]))
			{
				(*i)--;
				break ;
			}
			if (ft_iswhitespace(input[*i + 1]) || !input[*i + 1])
			{
				cmd->value[idx->j++]
					= ft_strrdup(input, idx->i, *i, cmd->shell->to_free);
				idx->i = *i + 1;
				while (ft_iswhitespace(input[idx->i]))
					idx->i++;
				*i = idx->i - 1;
			}
		}
		(*i)++;
	}
}

void	set_cmd_content(t_cmd *cmd, char *input, int *i, t_shell *shell)
{
	t_index		idx;
	t_parser	parser;
	int			args;

	idx.i = 0;
	idx.j = 1;
	parser.s_quote = 0;
	parser.d_quote = 0;
	args = count_args(&input[*i]);
	cmd_bzero(cmd, args + 2);
	while (input[*i])
	{
		quote_cmd(&parser, input[*i]);
		if (!parser.s_quote && !parser.d_quote && is_sep(input[*i]))
			break ;
		(*i)++;
		idx.i++;
	}
	cmd->value[0] = ft_strrdup(input, *i - idx.i, *i - 1, shell->to_free);
	while (ft_iswhitespace(input[*i]))
		(*i)++;
	idx.i = *i;
	cmd_content_loop(cmd, input, i, &idx);
	if (idx.i < *i)
		cmd->value[idx.j++] = ft_strrdup(input, idx.i, *i, shell->to_free);
}
