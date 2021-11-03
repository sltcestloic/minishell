#include "minishell.h"

int	is_redirect(char *str, int *i)
{
	if (str[*i] == '>')
	{
		(*i)++;
		if (str[*i] == '>')
		{
			(*i)++;
			return (2);
		}
		return (1);
	}
	else if (str[*i] == '<')
	{
		(*i)++;
		if (str[*i] == '<')
		{
			(*i)++;
			return (4);
		}
		return (3);
	}
	return (0);
}

void	init_redirect_by_type(t_cmd *cmd, int type, int *init,
								t_redirect **redirect)
{
	if (type < 3)
	{
		if (!cmd->out)
		{
			cmd->out = malloc(sizeof(t_redirect));
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
			cmd->in = malloc(sizeof(t_redirect));
			cmd->in->file_name = NULL;
			cmd->in->next = NULL;
			*init = 1;
		}
		*redirect = cmd->in;
	}
}

int	init_redirect_io(t_cmd *cmd, int type)
{
	t_redirect	*redirect;
	int			init;

	init = 0;
	init_redirect_by_type(cmd, type, &init, &redirect);
	if (!redirect)
		return (0);
	redirect->variation = type == 2 || type == 4;
	if (!init)
		redirect_addback(redirect, type);
	return (1);
}

void	init_redirect(t_cmd *cmd, int type)
{
	int	ret;

	ret = init_redirect_io(cmd, type);
	if (!ret)
	{
		cmd_free(cmd);
		return ;
	}
}

int	set_file_name(t_shell *shell, t_redirect *redirect, char *input, int *i)
{
	int			j;
	t_redirect	*last;
	t_parser	parser;

	j = 0;
	parser = init_parser_nml();
	last = redirect_last(redirect);
	while (ft_iswhitespace(input[*i]))
		(*i)++;
	while (input[*i])
	{
		quote_cmd(&parser, input[*i]);
		if (!parser.s_quote && !parser.d_quote && is_sep(input[*i]))
			break ;
		(*i)++;
		j++;
	}
	if (j == 0)
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
