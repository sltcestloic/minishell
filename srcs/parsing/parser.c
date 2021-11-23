/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 08:47:09 by lbertran          #+#    #+#             */
/*   Updated: 2021/11/23 12:07:13 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(char *input)
{
	t_parser	parser;
	int			i;
	int			result;

	parser.s_quote = 0;
	parser.d_quote = 0;
	i = 0;
	result = 0;
	while (input[i])
	{
		if (ft_iswhitespace(input[i]) && input[i + 1]
			&& !ft_iswhitespace(input[i + 1])
			&& !parser.s_quote && !parser.d_quote && !is_sep(input[i + 1]))
			result++;
		else if (input[i] == '"' && !parser.s_quote)
			parser.d_quote = !parser.d_quote;
		else if (input[i] == '\'' && !parser.d_quote)
			parser.s_quote = !parser.s_quote;
		i++;
	}
	return (result);
}

void	print_struct_debug(t_cmd *cmd)
{
	t_cmd *tmp = cmd;
	t_redirect	*redirect;
	int count = 0;
	while (tmp)
	{
		redirect = tmp->redirect;
		printf("----------cmd #%d----------\n", count);
		if (tmp->value)
		{
			for (int n = 0; tmp->value[n]; n++)
				printf("cmd->value[%d] = |%s|\n", n, tmp->value[n]);
		}
		int k = 0;
		if (redirect)
		{
			printf(" redirects:\n");
			while (redirect)
			{
				printf("  (%p) redirect #%d:\n", redirect, k);
				printf("   cmd->redirect->file_name = |%s|\n", redirect->file_name);
				printf("   cmd->redirect->type = %d\n", redirect->type);
				k++;
				redirect = redirect->next;
			}
		}
		tmp = tmp->next;
		count++;
	}
}
static int	handle_redirect(char *input, t_parser *parser, t_cmd *cmd, int *i)
{
	init_redirect(cmd_last(cmd), parser->redirect);
	return (set_file_name(cmd->shell, cmd_last(cmd)->redirect, input, i));
}

static void	handle_cmd(char *input, t_cmd *cmd, int *i, t_shell *shell)
{
	if (cmd_last(cmd)->value)
	{
		if (input[*i - 1] == '\'' || input[*i - 1] == '"'
			|| input[*i - 1] == '\'')
			*i += add_arg(cmd_last(cmd), &input[*i - 1], shell);
		else
			*i += add_arg(cmd_last(cmd), &input[*i], shell);
	}
	else
		set_cmd_content(cmd_last(cmd), input, i, shell);
}

static void	substitution(t_shell *shell, t_cmd *cmd)
{
	t_cmd		*tmp;

	tmp = cmd;
	if (substitute(shell, cmd))
	{
		while (tmp)
		{
			if (tmp->redirect && !tmp->redirect->file_name)
			{
				g_last_exit = 258;
				printf("minishell: invalid input: bad redirect.\n");
				return ;
			}
			redo_value(tmp);
			tmp = tmp->next;
		}
		print_struct_debug(cmd);
		cmd_parse(cmd, shell);
	}
}

void	parse_input(char *input, t_shell *shell)
{
	t_cmd		*cmd;
	int			i;
	t_parser	*parser;

	parser = init_parser(shell);
	i = -1;
	cmd = init_cmd(shell);
	while (input[++i])
	{
		parser->redirect = is_redirect(input, &i);
		if (parser->redirect)
		{
			if (!handle_redirect(input, parser, cmd, &i))
				break ;
			if (!input[i])
				break ;
		}
		else if (input[i] == '|')
			add_new_cmd(cmd, shell);
		else if (!ft_iswhitespace(input[i]))
			handle_cmd(input, cmd, &i, shell);
		if (!input[i])
			break ;
	}
	substitution(shell, cmd);
}
