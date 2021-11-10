#include "minishell.h"

static void	quote(t_parser *parser, t_cmd *cmd, char c)
{
	if (c == '"' && !parser->s_quote)
	{
		parser->d_quote = !parser->d_quote;
		cmd->quotes++;
	}
	else if (c == '\'' && !parser->d_quote)
	{
		parser->s_quote = !parser->s_quote;
		cmd->quotes++;
	}
}

void	substitute_loop_body(t_cmd *cmd, t_parser *parser, t_index *idx,
		char *new_value)
{
	quote(parser, cmd, cmd->value[idx->i][idx->j]);
	if (cmd->value[idx->i][idx->j] == '\\'
		&& is_quote(cmd->value[idx->i][idx->j + 1]))
		new_value[idx->k++] = cmd->value[idx->i][++idx->j];
	if (is_non_removable(parser, cmd->value[idx->i][idx->j]))
		new_value[idx->k++] = cmd->value[idx->i][idx->j];
	new_value[idx->k] = 0;
	idx->j++;
}

static void	substitute_quotes(t_shell *shell, t_cmd *cmd)
{
	t_index		idx;
	t_parser	parser;
	char		*new_value;

	idx = init_index();
	parser = init_parser_nml();
	while (cmd->value[idx.i])
	{
		if (cmd->value[idx.i] == (char *)1)
		{
			idx.i++;
			continue ;
		}
		new_value = ft_malloc(sizeof(char)
				* (ft_strlen(cmd->value[idx.i]) + 1), &shell->to_free);
		while (cmd->value[idx.i][idx.j])
			substitute_loop_body(cmd, &parser, &idx, new_value);
		cmd->value[idx.i] = new_value;
		idx.i++;
		idx.j = 0;
		idx.k = 0;
	}
}

static int	error(char *str)
{
	printf("%s", str);
	return (0);
}

int	substitute(t_shell *shell, t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (!tmp->value && !tmp->in && !tmp->out)
		{
			printf("minishell: invalid command\n");
			return (0);
		}
		if (!tmp->value)
		{
			tmp = tmp->next;
			continue ;
		}
		substitute_env_vars(shell, tmp);
		split_tokens(tmp);
		substitute_quotes(shell, tmp);
		if (!substitute_redirect_quotes(shell, cmd))
			return (error("minishell: invalid input: bad redirect.\n"));
		if (cmd->quotes % 2 != 0)
			return (error("minishell: invalid input: unclosed quotes.\n"));
		tmp = tmp->next;
	}
	return (1);
}
