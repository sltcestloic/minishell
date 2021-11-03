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
		printf("dest[%d] = %s\n", i, dest[i]);
		i++;
		printf("i=%d\n", i);
	}
	printf("dest[%d] = 0\n", i);
	dest[i] = 0;
}

void	split_cmd(t_cmd *cmd, int index, int spaces)
{
	char	**new_value;
	char	**end_value;
	int		i;
	int		j;
	int		last;

	i = 0;
	j = 0;
	last = 0;
	new_value = malloc(sizeof(char *) * (ft_splitlen(cmd->value) + spaces + 1));
	end_value = malloc(sizeof(char *) * (ft_splitlen(&cmd->value[index]) + 1));
	copy_content(&cmd->value[index + 1], end_value);
	while (j < index - 1)
	{
		new_value[j] = ft_strdup(cmd->value[j], NULL);
		j++;
	}
	while (cmd->value[index][i])
	{
		if (cmd->value[index][i] == ' ')
		{
			new_value[j++] = ft_strrdup(cmd->value[index], last, i - 1, NULL);
			printf("new_value[%d] = %s\n", j - 1, new_value[j - 1]);
			last = i + 1;
		}
		i++;
	}
	new_value[j++] = ft_strrdup(cmd->value[index], last, i - 1, NULL);
	printf("new_value[%d] = %s\n", j - 1, new_value[j - 1]);
	copy_content(end_value, &new_value[j]);
	copy_content(new_value, cmd->value);
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