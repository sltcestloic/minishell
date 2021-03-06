/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 08:46:53 by lbertran          #+#    #+#             */
/*   Updated: 2021/11/20 16:35:06 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_redirect_by_type(t_cmd *cmd, int type, int *init)
{
	if (!cmd->redirect)
	{
		cmd->redirect = (t_redirect *)ft_malloc(
				sizeof(t_redirect), &cmd->shell->to_free);
		if (!cmd->redirect)
			ft_malloc_error(cmd->shell->to_free);
		cmd->redirect->file_name = NULL;
		cmd->redirect->next = NULL;
		cmd->redirect->type = type;
		*init = 1;
	}
}

int	init_redirect_io(t_cmd *cmd, int type)
{
	int			init;

	init = 0;
	init_redirect_by_type(cmd, type, &init);
	if (!init)
		redirect_addback(cmd->redirect, type, cmd->shell);
	return (1);
}

void	init_redirect(t_cmd *cmd, int type)
{
	int	ret;

	ret = init_redirect_io(cmd, type);
	if (!ret)
		ft_malloc_error(cmd->shell->to_free);
}

static int	get_name_len(char *input, t_parser parser, int *j, int *i)
{
	while (ft_iswhitespace(input[*i]))
		(*i)++;
	while (input[*i])
	{
		quote_cmd(&parser, input[*i]);
		if (!parser.s_quote && !parser.d_quote && is_sep(input[*i]))
			break ;
		(*i)++;
		(*j)++;
	}
	if (*j == 0)
		return (-1);
	return (1);
}

int	set_file_name(t_shell *shell, t_redirect *redirect, char *input, int *i)
{
	int			j;
	t_redirect	*last;
	t_parser	parser;

	j = 0;
	parser = init_parser_nml();
	last = redirect_last(redirect);
	if (get_name_len(input, parser, &j, i) != 1)
		return (-1);
	last->file_name = ft_malloc(sizeof(char) * (j + 1), &shell->to_free);
	if (!last->file_name)
		ft_malloc_error(shell->to_free);
	*i -= j;
	j = 0;
	while (input[*i])
	{
		quote_cmd(&parser, input[*i]);
		if (!parser.s_quote && !parser.d_quote && is_sep(input[*i]))
			break ;
		last->file_name[j++] = input[*i];
		(*i)++;
	}
	last->file_name[j] = '\0';
	return (1);
}
