/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 08:46:53 by lbertran          #+#    #+#             */
/*   Updated: 2021/11/17 08:46:54 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_redirect_by_type(t_cmd *cmd, int type, int *init,
								t_redirect **redirect)
{
	if (type < 3)
	{
		if (!cmd->out)
		{
			cmd->out = (t_redirect *)ft_malloc(
					sizeof(t_redirect), &cmd->shell->to_free);
			cmd->out->file_name = NULL;
			cmd->out->next = NULL;
			*init = 1;
		}
		*redirect = cmd->out;
	}
	else
	{
		if (!cmd->in)
		{
			cmd->in = (t_redirect *)ft_malloc(
					sizeof(t_redirect), &cmd->shell->to_free);
			cmd->in->file_name = NULL;
			cmd->in->next = NULL;
			*init = 1;
		}
		*redirect = cmd->in;
	}
	(*redirect)->variation = 0;
}

int	init_redirect_io(t_cmd *cmd, int type)
{
	t_redirect	*redirect;
	int			init;

	init = 0;
	init_redirect_by_type(cmd, type, &init, &redirect);
	if (!redirect)
		ft_malloc_error(cmd->shell->to_free);
	if (type == 2 || type == 4)
		redirect->variation = 1;
	if (!init)
		redirect_addback(redirect, type, cmd->shell);
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
