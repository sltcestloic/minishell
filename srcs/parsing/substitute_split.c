#include "minishell.h"

int	has_space(char *str)
{
	int			i;
	int			count;
	t_parser	parser;

	i = 0;
	count = 0;
	parser = init_parser_nml();
	while (str[i])
	{
		quote_cmd(&parser, str[i]);
		if (str[i] == ' ' && !parser.s_quote && !parser.d_quote)
			count++;
		i++;
	}
	return (count);
}

void	copy_content(char **src, char **dest)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = ft_strdup(src[i], NULL);
		i++;
	}
	dest[i] = 0;
}

static void	copy_first_values(t_index *idx, int index,
			char **new_value, t_cmd *cmd)
{
	while (idx->j < index)
	{
		new_value[idx->j] = ft_strdup(cmd->value[idx->j], NULL);
		idx->j++;
	}
}

void	split_cmd(t_cmd *cmd, int index, int spaces)
{
	char	**new_value;
	char	**end_value;
	t_index	idx;
	int		last;

	idx = init_index();
	last = 0;
	new_value = (char **)ft_malloc(sizeof(char *) * (ft_splitlen(cmd->value) + spaces + 1), &cmd->shell->to_free);
	end_value = (char **)ft_malloc(sizeof(char *) * (ft_splitlen(&cmd->value[index]) + 1), &cmd->shell->to_free);
	copy_content(&cmd->value[index + 1], end_value);
	copy_first_values(&idx, index, new_value, cmd);
	while (cmd->value[index][idx.i])
	{
		if (cmd->value[index][idx.i] == ' ')
		{
			new_value[idx.j++]
				= ft_strrdup(cmd->value[index], last, idx.i - 1, NULL);
			last = idx.i + 1;
		}
		idx.i++;
	}
	new_value[idx.j++] = ft_strrdup(cmd->value[index], last, idx.i - 1, NULL);
	copy_content(end_value, &new_value[idx.j]);
	cmd->value = new_value;
}

void	split_tokens(t_cmd *cmd)
{
	int	i;
	int	spaces;

	i = 0;
	while (cmd->value[i])
	{
		spaces = has_space(cmd->value[i]);
		if (spaces > 0)
			split_cmd(cmd, i, spaces);
		i++;
	}
}
