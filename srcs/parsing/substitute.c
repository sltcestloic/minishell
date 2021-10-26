#include "minishell.h"

static void	substitute_env_vars(t_shell *shell, t_cmd *cmd)
{
	t_index	idx;
	char	*tmp;

	idx.i = 1;
	idx.j = 0;
	while (cmd->value[idx.i])
	{
		idx.k = has_env_var(cmd->value[idx.i], shell);
		if (idx.k != -1)
		{
			tmp = substitute_env_var(shell, cmd->value[idx.i], idx.k);
			free(cmd->value[idx.i]);
			cmd->value[idx.i] = tmp;
			continue ;
		}
		idx.i++;
	}
}

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

static int	is_non_removable(t_parser *parser, char c)
{
	if (c != '\'' && c != '"')
		return (1);
	else if (c == '\'' && parser->d_quote)
		return (1);
	else if (c == '"' && parser->s_quote)
		return (1);
	else
		return (0);
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
		new_value = ft_malloc(sizeof(char)
				* (ft_strlen(cmd->value[idx.i]) + 1), &shell->to_free);
		while (cmd->value[idx.i][idx.j])
		{
			quote(&parser, cmd, cmd->value[idx.i][idx.j]);
			if (cmd->value[idx.i][idx.j] == '\\'
				&& is_quote(cmd->value[idx.i][idx.j + 1]))
				new_value[idx.k++] = cmd->value[idx.i][++idx.j];
			if (is_non_removable(&parser, cmd->value[idx.i][idx.j]))
				new_value[idx.k++] = cmd->value[idx.i][idx.j];
			new_value[idx.k] = 0;
			idx.j++;
		}
		free(cmd->value[idx.i]);
		cmd->value[idx.i] = new_value;
		idx.i++;
		idx.j = 0;
		idx.k = 0;
	}
}

int	substitute(t_shell *shell, t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (!tmp->value)
		{
			printf("minishell: invalid command\n");
			return (0);
		}
		substitute_env_vars(shell, tmp);
		substitute_quotes(shell, tmp);
		if (cmd->quotes % 2 != 0)
		{
			printf("Invalid input: unclosed quotes. (%d)\n", cmd->quotes);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
