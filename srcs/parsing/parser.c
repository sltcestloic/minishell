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
	t_redirect	*r_in;
	t_redirect	*r_out;
	int count = 0;
	while (tmp)
	{
		r_in = tmp->in;
		r_out = tmp->out;
		printf("----------cmd #%d----------\n", count);
		if (tmp->value)
		{
			printf("value !\n");
			printf("ptr%p\n", tmp->value[0]);
			for (int n = 0; tmp->value[n]; n++)
				printf("cmd->value[%d] = |%s|\n", n, tmp->value[n]);
			printf("cc\n");
		}
		int k = 0;
		if (r_in)
		{
			printf(" redirect in:\n");
			while (r_in)
			{
				printf("  (%p) redirect #%d:\n", r_in, k);
				printf("   cmd->in->file_name = %s\n", r_in->file_name);
				printf("   cmd->in->variation = %d\n", r_in->variation);
				k++;
				r_in = r_in->next;
			}
		}
		if (r_out)
		{
			printf(" redirect out:\n");
			k = 0;	
			while (r_out)
			{
				printf("  (%p) redirect #%d:\n", r_out, k);
				printf("   cmd->out->file_name = %s\n", r_out->file_name);
				printf("   cmd->out->variation = %d\n", r_out->variation);
				k++;
				r_out = r_out->next;
			}
		}
		tmp = tmp->next;
		count++;
	}
 }
static int	handle_redirect(char *input, t_parser *parser, t_cmd *cmd, int *i)
{
	init_redirect(cmd_last(cmd), parser->redirect);
	if (parser->redirect < 3)
		return (set_file_name(cmd->shell, cmd_last(cmd)->out, input, i));
	else
		return (set_file_name(cmd->shell, cmd_last(cmd)->in, input, i));
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
			if ((tmp->out && !tmp->out->file_name)
				|| (tmp->in && !tmp->in->file_name))
			{
				printf("minishell: invalid input: bad redirect.\n");
				return ;
			}
			redo_value(tmp);
			tmp = tmp->next;
		}
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
