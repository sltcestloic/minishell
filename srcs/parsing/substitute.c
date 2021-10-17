#include "minishell.h"

static int	has_env_var(char *input)
{
	t_parser	*parser;
	int			i;

	parser = init_parser();
	i = 0;
	while (input[i])
	{
		if (input[i] == '"' && !parser->s_quote)
			parser->d_quote = !parser->d_quote;
		else if (input[i] == '\'' && !parser->d_quote)
			parser->s_quote = !parser->s_quote;
		else if (input[i] == '$' && !parser->s_quote)
		{
			free(parser);
			return (i);
		}
		i++;
	}
	free(parser);
	return (-1);
}

static char	*substitute_env_var(t_shell *shell, char *input, int var)
{
	char	*ret;
	char	*var_name;
	char	*new_var;
	char	*end;
	int		i;

	ret = NULL;
	if (var > 0)
		ret = ft_strrdup(input, 0, var - 1);
	i = var;
	while (input[i] && (ft_isalnum(input[i]) || input[i] == '?' || i == var))
	{
		i++;
	}
	var_name = ft_strrdup(input, var, i - 1);
	new_var = get_env_var(shell, var_name);
	free(var_name);
	ret = ft_strjoin(ret, new_var);
	free(new_var);
	if ((int)ft_strlen(input) > i)
	{
		end = ft_strrdup(input, i, ft_strlen(input) - 1);
		ret = ft_strjoin(ret, end);
		free(end);
	}
	return (ret);
}

/*
** idx.k = var $ index
*/
static void	substitute_env_vars(t_shell *shell, t_cmd *cmd)
{
	t_index	idx;
	char	*tmp;

	idx.i = 1;
	idx.j = 0;
	while (cmd->value[idx.i])
	{
		idx.k = has_env_var(cmd->value[idx.i]);
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

static void	substitute_quotes(t_cmd *cmd)
{
	t_index		idx;
	t_parser	parser;
	char		*new_value;

	idx.i = 0;
	idx.j = 0;
	idx.k = 0;
	parser.d_quote = 0;
	parser.s_quote = 0;
	while (cmd->value[idx.i])
	{
		new_value = malloc(sizeof(char) * (ft_strlen(cmd->value[idx.i]) + 1));
		if (!new_value)
			return; //TODO exit ?
		*new_value = 0;
		while (cmd->value[idx.i][idx.j])
		{
			if (cmd->value[idx.i][idx.j] == '"' && !parser.s_quote)
			{
				parser.d_quote = !parser.d_quote;
				cmd->quotes++;
			}
			else if (cmd->value[idx.i][idx.j] == '\'' && !parser.d_quote)
			{
				parser.s_quote = !parser.s_quote;
				cmd->quotes++;
			}
			else
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

int		substitute(t_shell *shell, t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (!tmp->value)
		{
			printf("Minishell: invalid command\n");
			return (0);
		}
		substitute_env_vars(shell, cmd);
		substitute_quotes(cmd);
		if (cmd->quotes % 2 != 0)
		{
			printf("Invalid input: unclosed quotes.\n");
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
