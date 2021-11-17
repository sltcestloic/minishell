/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_redirect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 08:46:57 by lbertran          #+#    #+#             */
/*   Updated: 2021/11/17 08:46:58 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	quote(t_parser *parser, t_redirect *redirect, char c)
{
	if (c == '"' && !parser->s_quote)
	{
		parser->d_quote = !parser->d_quote;
		redirect->quotes++;
	}
	else if (c == '\'' && !parser->d_quote)
	{
		parser->s_quote = !parser->s_quote;
		redirect->quotes++;
	}
}

static void	substitute_loop_body(t_redirect *redirect, t_parser *parser,
		t_index *idx, char *new_value)
{
	quote(parser, redirect, redirect->file_name[idx->i]);
	if (redirect->file_name[idx->i] == '\\'
		&& is_quote(redirect->file_name[idx->i + 1]))
		new_value[idx->k++] = redirect->file_name[++idx->i];
	if (is_non_removable(parser, redirect->file_name[idx->i]))
		new_value[idx->k++] = redirect->file_name[idx->i];
	new_value[idx->k] = 0;
	idx->i++;
}

static int	do_substitute(t_shell *shell, t_redirect *redirect)
{
	t_index		idx;
	t_parser	parser;
	char		*new_value;

	idx = init_index();
	parser = init_parser_nml();
	while (redirect)
	{
		if (!redirect->file_name)
			return (0);
		new_value = ft_malloc(sizeof(char)
				* (ft_strlen(redirect->file_name) + 1), &shell->to_free);
		while (redirect->file_name[idx.i])
			substitute_loop_body(redirect, &parser, &idx, new_value);
		redirect->file_name = new_value;
		idx.i = 0;
		redirect = redirect->next;
		idx.k = 0;
	}
	return (1);
}

int	substitute_redirect_quotes(t_shell *shell, t_cmd *cmd)
{
	if (cmd->in)
		if (!do_substitute(shell, cmd->in))
			return (0);
	if (cmd->out)
		if (!do_substitute(shell, cmd->out))
			return (0);
	return (1);
}
